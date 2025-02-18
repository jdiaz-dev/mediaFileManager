#include <utility> // for std::pair
#include "FilesController.h"
#include <drogon/MultiPart.h>
#include <drogon/HttpRequest.h>
#include "../validators/FieldValuesChecker.h"
#include "../validators/RequestFormatValidator.h"

using namespace std;
using namespace drogon;

void FilesController::saveFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    try {
        MultiPartParser multiparser;
        int parsedRequest = multiparser.parse(req); 
        string name = "entity";
        unordered_map<string, variant<string, vector<string>>> validFields = {{"entity", ""}, {"files", vector<string>{}}};

        RequestFormatValidator::validateFormDataFormat(parsedRequest);
        FieldValuesChecker fieldValuesChecker(multiparser, validFields);
        fieldValuesChecker.validateFields();
        fieldValuesChecker.validateFieldValues();

        //upload files
        vector<string> fileNames;
        auto files = multiparser.getFiles();
        for (const auto &file : files) {
            fileNames.push_back(file.getFileName());
            file.save("./uploads/" + file.getFileName());  // Save uploaded file
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
        resp->setBody(R"({"error": ")" + std::string(e.what()) + R"("})");
        callback(resp);
        return;
    }
    
}

