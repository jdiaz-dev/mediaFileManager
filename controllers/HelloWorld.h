#pragma once
#include <drogon/HttpController.h>

using namespace drogon;

class HelloWorld : public HttpController<HelloWorld> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HelloWorld::hello, "/hello", Get);
    METHOD_LIST_END

    void hello(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback);
};
