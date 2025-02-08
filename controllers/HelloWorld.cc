#include "HelloWorld.h"
#include <json/json.h>

void HelloWorld::hello(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback) {
    Json::Value json;
    json["message"] = "Hello, Drogon!";
    
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
