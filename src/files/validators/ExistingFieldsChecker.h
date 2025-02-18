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
    protected:
        MultiPartParser multiparser;
        unordered_map<string, variant<string, vector<string>>> validFields;
    private: 
        unordered_map<string, bool> fieldsToValidate;
        void initializeValidatedFields();
        void analyzeInParameters();
        void analyzeInFiles();
        void checkFields();
    public:
        ExistingFieldsChecker(MultiPartParser& multiparser, unordered_map<string, variant<string, vector<string>>>& validFields);
        void validateFields();
};

    

    