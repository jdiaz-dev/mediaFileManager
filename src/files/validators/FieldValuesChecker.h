#pragma once
#include <unordered_set>
#include <stdexcept>
#include <vector>
#include <variant> 
#include <string>
#include "ExistingFieldsChecker.h"

using namespace std;

class FieldValuesChecker {
    private:
        static const unordered_set<string> validActions;
        static const string actionsAsString;
        static const unordered_set<string> validFileFormats;

        void isValidAction();
        void isValidFileFormat(const std::string& filename);
        void validateFileFormats();
    public:
        unordered_map<string, variant<string, vector<string>>> validFields;
        FieldValuesChecker(unordered_map<string, variant<string, vector<string>>>& validFields); 
        void validateFieldValues();
};
