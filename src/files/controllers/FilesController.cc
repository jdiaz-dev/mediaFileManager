#include "FilesController.h"
#include <drogon/MultiPart.h>
#include <drogon/HttpRequest.h>
#include "../validators/SaveMediaFilesDto.h"
#include "../validators/RequestFormatValidator.h"
#include "../validators/ValidateFieldsPresence.h"

using namespace std;
using namespace drogon;

void FilesController::saveFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {

    MultiPartParser multiparser;
    int parsedRequest = multiparser.parse(req); 
    unordered_map<string, bool> fieldsToValidate = {{"entity", false}, {"files", false}};

   RequestFormatValidator::validateFormDataFormat(parsedRequest);
   ValidateFieldsPresence ValidateFieldsPresence(multiparser, fieldsToValidate);
    
    std::vector<drogon::HttpFile> filesito = multiparser.getFiles();
    auto yuju = next(filesito.begin(), 0)->getItemName();

    //validate files key
    bool hasFilesKey = false;
        cout << "feo = " << yuju << endl;
    for (const auto &file : multiparser.getFiles()) {
        cout << "value = " << file.getItemName() << endl;
        if (file.getItemName() == "files") {  // Check if the key name matches
            hasFilesKey = true;
            break;
        }
    }

    //validate entity key
    auto parameters = multiparser.getParameters();
    std::string entity;
    if (parameters("entity") != parameters.end()) {
        entity = parameters["entity"];
    } else {
        LOG_ERROR << "Missing 'entity' field";
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
        resp->setBody(R"({"error": "Missing entity field"})");
        callback(resp);
        return;
    }

    //upload files
    std::vector<std::string> fileNames;
    auto files = multiparser.getFiles();
    for (const auto &file : files) {
        fileNames.push_back(file.getFileName());
        file.save("./uploads/" + file.getFileName());  // Save uploaded file
    }

//validate existense of parameters and existense of files
    if (parameters.empty() || multiparser.getFiles().empty()) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
        resp->setBody(R"({"error": "Missing form fields"})");
        callback(resp);
        return;
    }

    try {
        SaveMediaFilesDto media(entity, fileNames);
        media.verifyValidParameters(parameters);
        media.validate(); // Call validation function
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