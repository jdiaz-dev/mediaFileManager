#pragma once
#include <drogon/HttpController.h>

using namespace drogon;

class HealthCheckController : public HttpController<HealthCheckController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HealthCheckController::ping, "/ping", Get);
    METHOD_LIST_END

    void ping(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback);
};
