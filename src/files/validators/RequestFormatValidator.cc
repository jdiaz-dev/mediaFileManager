#include "RequestFormatValidator.h"
#include <drogon/HttpRequest.h>
#include <stdexcept> 

using namespace std;

void RequestFormatValidator::validateFormDataFormat(const int& parsedRequest){
    if (parsedRequest != 0) {
        LOG_ERROR << "Failed to parse multipart form-data";
        throw invalid_argument("Invalid multipart form-data!");
    }
}


