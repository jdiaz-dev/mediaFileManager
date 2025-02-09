#include "FilesController.h"
#include <drogon/HttpResponse.h>

using namespace drogon;

void FilesController::saveFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    // Extract form-data parameters

    MultiPartParser multiparser;
    multiparser.parse(req);
    std::string file = multiparser.getFiles()[0].getFileName();

    auto parameters = multiparser.getParameters();

    if (parameters.empty() || file.empty()) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
        resp->setBody(R"({"error": "Missing form fields"})");
        callback(resp);
        return;
    }

    // Print debug info
    // LOG_DEBUG << "Entity: " << entity;
    LOG_DEBUG << "File Data: " << file.substr(0, 100) << "...";  // Limit log output

    // Create response
    Json::Value response;
    response["message"] = "Upload successful!";
    // response["entity"] = entity;

    auto resp = HttpResponse::newHttpJsonResponse(response);
    callback(resp);
}
