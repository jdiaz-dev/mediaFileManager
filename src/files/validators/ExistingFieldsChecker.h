#pragma once
#include <stdexcept>
#include <variant> 
#include <vector>
#include <string>
#include <unordered_set>
#include <drogon/MultiPart.h> 

using namespace std;
using namespace drogon;

class ExistingFieldsChecker {
    private: 
        MultiPartParser multiparser;
        unordered_map<string, bool> fieldsToValidate;
        vector<HttpFile> files;
        void initializeFieldsToValidate();
        void analyzeInParameters();
        void analyzeInFiles();
        void checkFields();
    public:
        unordered_map<string, variant<string, vector<string>>> validFields;
        ExistingFieldsChecker(MultiPartParser& multiparser, unordered_map<string, variant<string, vector<string>>>& validFields);
        void validateFields();
};

    

    