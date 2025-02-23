// #pragma once
#include <drogon/HttpController.h>

using namespace drogon;

class FilesController : public drogon::HttpController<FilesController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(FilesController::saveFile, "/file", Post);
    METHOD_LIST_END

    //(const HttpResponsePtr &): is a smart pointer : https://www.geeksforgeeks.org/smart-pointers-cpp/
    //&&: rvalue reference : https://www.geeksforgeeks.org/lvalues-references-and-rvalues-references-in-c-with-examples/
    void saveFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
};
