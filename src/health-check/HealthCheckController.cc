#include "HealthCheckController.h"
#include <json/json.h>

void HealthCheckController::ping(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback) {
    Json::Value json;
    json["message"] = "Pong!";
    
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
