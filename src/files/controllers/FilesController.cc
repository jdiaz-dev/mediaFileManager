#include <variant> 
#include <memory>
#include <utility> // for std::pair
#include <vips/vips8>
#include <drogon/MultiPart.h>
#include <drogon/HttpRequest.h>

#include "FilesController.h"
#include "../validators/FieldValuesChecker.h"
#include "../validators/RequestFormatValidator.h"
#include "../services/MediaFilesManagerService.h"
#include "../services/ImageCompressorService.h"

using namespace vips;

using namespace std;
using namespace drogon;

void FilesController::saveFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    try {
        MultiPartParser multiparser;
        int parsedRequest = multiparser.parse(req); 
        RequestFormatValidator::validateFormDataFormat(parsedRequest);
       
        unordered_map<string, variant<string, vector<string>>> validFields = {{"action", ""}, {"files", vector<string>{}}};
        ExistingFieldsChecker existingFieldsChecker(multiparser, validFields);
        existingFieldsChecker.validateFields();
        FieldValuesChecker fieldValuesChecker(existingFieldsChecker.validFields);
        fieldValuesChecker.validateFieldValues();

        vector<string> savedFiles = existingFieldsChecker.saveFiles();
        MediaFilesManagerService mediaFilesManagerService(make_shared<ImageCompressorService>());
        mediaFilesManagerService.compressFiles(savedFiles);
        // Create response
        Json::Value response;
        response["message"] = "Compression completed!";
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
