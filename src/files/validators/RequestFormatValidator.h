#pragma once
#include <drogon/HttpRequest.h>

class RequestFormatValidator {
public:
    static void validateFormDataFormat(const int& parsedRequest){
        if (parsedRequest != 0) {
            LOG_ERROR << "Failed to parse multipart form-data";
            throw invalid_argument("Invalid multipart form-data!");
        }
    }
};
