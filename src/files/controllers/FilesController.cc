#include <filesystem> 
#include <variant> 
#include <utility> // for std::pair
#include "FilesController.h"
#include <drogon/MultiPart.h>
#include <drogon/HttpRequest.h>
#include "../validators/FieldValuesChecker.h"
#include "../validators/RequestFormatValidator.h"
#include <vips/vips8>

using namespace vips;

using namespace std;
using namespace drogon;

void FilesController::saveFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    try {
        MultiPartParser multiparser;
        int parsedRequest = multiparser.parse(req); 
        RequestFormatValidator::validateFormDataFormat(parsedRequest);
       
        unordered_map<string, variant<string, vector<string>>> validFields = {{"action", ""}, {"files", vector<string>{}}};
        FieldValuesChecker fieldValuesChecker(multiparser, validFields);
        fieldValuesChecker.validateFields();
        fieldValuesChecker.validateFieldValues();

        //upload files
        /* vector<string> fileNames;
        auto files = multiparser.getFiles();
        for (const auto &file : files) {
            fileNames.push_back(file.getFileName());
            file.save("./uploads/" + file.getFileName());  // Save uploaded file
        } */

        for (const auto& file : multiparser.getFiles()) {
            std::string keyName = file.getItemName();
            std::string fileName = file.getFileName();
            // ✅ Define the path where the file will be temporarily saved
            std::string tempPath = "./files/" + fileName;

            // ✅ Save the file manually (Drogon does not provide a temp path)
            if (file.saveAs(tempPath) != 0) {
                auto resp = HttpResponse::newHttpResponse();
                resp->setStatusCode(k500InternalServerError);
                resp->setBody(R"({"error": "Failed to save uploaded file!"})");
                callback(resp);
                return;
            }

            // ✅ Check if the file is an image
            if (fileName.rfind(".jpg") || fileName.rfind(".jpeg") || fileName.rfind(".png") || fileName.rfind(".webp")) {
                std::string compressedPath = "./compressed/" + fileName;
                if (compressImage(tempPath, compressedPath, 75)) {  // ✅ Compress image
                    Json::Value jsonResponse;
                    jsonResponse["message"] = "File uploaded and compressed successfully!";
                    jsonResponse["file"] = compressedPath;

                    auto resp = HttpResponse::newHttpJsonResponse(jsonResponse);
                    callback(resp);

                } else {
                    auto resp = HttpResponse::newHttpResponse();
                    resp->setStatusCode(k500InternalServerError);
                    resp->setBody(R"({"error": "Failed to compress image!"})");
                    callback(resp);
                }
            } else {
                auto resp = HttpResponse::newHttpResponse();
                resp->setStatusCode(k415UnsupportedMediaType);
                resp->setBody(R"({"error": "Unsupported file format!"})");
                callback(resp);
            }
        }

        // Create response
        Json::Value response;
        response["message"] = "Upload successful!";
        // response["entity"] = entity;

        auto resp = HttpResponse::newHttpJsonResponse(response);
        callback(resp);

    } catch (const std::exception &e) {
        LOG_ERROR << "Validation Error: " << e.what();
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
        resp->setBody(R"({"error": ")" + string(e.what()) + R"("})");
        callback(resp);
        return;
    }
    
}

bool FilesController::compressImage(const std::string& inputPath, const std::string& outputPath, int quality) {
        if (VIPS_INIT("compress_image")) {
            std::cerr << "Failed to initialize VIPS" << std::endl;
            return false;
        }

        try {

            std::filesystem::path outputDir = std::filesystem::path(outputPath).parent_path();
            if (!std::filesystem::exists(outputDir)) {
                std::filesystem::create_directories(outputDir);  // ✅ Create directory if missing
            }
            VImage img = VImage::new_from_file(inputPath.c_str());

            if (outputPath.rfind(".jpg") || outputPath.rfind(".jpeg")) {
                img.jpegsave(outputPath.c_str(), VImage::option()->set("Q", quality));
            } else if (outputPath.rfind(".png")) {
                img.pngsave(outputPath.c_str(), VImage::option()->set("compression", 9));
            } else if (outputPath.rfind(".webp")) {
                img.webpsave(outputPath.c_str(), VImage::option()->set("Q", quality));
            } else {
                vips_error_exit("Unsupported format!");
                return false;
            }

            vips_shutdown();
            return true;
        } catch (const std::exception& e) {
            std::cerr << "VIPS Error: " << e.what() << std::endl;
            return false;
        }
    }
