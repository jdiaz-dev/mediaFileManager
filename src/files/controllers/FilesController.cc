#include <utility> // for std::pair
#include "FilesController.h"
#include <drogon/MultiPart.h>
#include <drogon/HttpRequest.h>
#include "../validators/SaveMediaFilesDto.h"
#include "../validators/RequestFormatValidator.h"
#include "../validators/ExistingFieldsChecker.h"

using namespace std;
using namespace drogon;

void FilesController::saveFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {

    MultiPartParser multiparser;
    int parsedRequest = multiparser.parse(req); 
    string name = "entity";
    unordered_map<string, variant<string, vector<string>>> validatedFields = {{"entity", ""}, {"files", vector<string>{}}};

    RequestFormatValidator::validateFormDataFormat(parsedRequest);
    ExistingFieldsChecker existingFieldsChecker(multiparser, validatedFields);
    existingFieldsChecker.validate();

    //upload files
    vector<string> fileNames;
    auto files = multiparser.getFiles();
    for (const auto &file : files) {
        fileNames.push_back(file.getFileName());
        file.save("./uploads/" + file.getFileName());  // Save uploaded file
    }

    try {
       /*  SaveMediaFilesDto media(entity, fileNames);
        media.verifyValidParameters(parameters);
        media.validate();  */
    } catch (const std::exception &e) {
        LOG_ERROR << "Validation Error: " << e.what();
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
        resp->setBody(R"({"error": ")" + std::string(e.what()) + R"("})");
        callback(resp);
        return;
    }

    

    // LOG_DEBUG << "Entity: " << entity;
    // LOG_DEBUG << "File Data: " << file.substr(0, 100) << "...";  // Limit log output

    // Create response
    Json::Value response;
    response["message"] = "Upload successful!";
    // response["entity"] = entity;

    auto resp = HttpResponse::newHttpJsonResponse(response);
    callback(resp);
}

/* 
    validate form-data format
    validatePresenceOfFields
    extract fields
    internal validation
        - entity: chats, users, avatars,
        - format type: pdf, .png, jpeg
    save file
 */