#pragma once
#include <unordered_set>
#include <stdexcept>
#include <vector>
#include <variant> 
#include <string>
#include "ExistingFieldsChecker.h"

using namespace std;

class FieldValuesChecker : public ExistingFieldsChecker {
    private:
        static const unordered_set<string> validEntities;
        static const string entitiesAsString;
        static const unordered_set<string> validFileFormats;

        void isValidEntity();
        void isValidFileFormat(const std::string& filename);
        void validateFileFormats();
    public:
        FieldValuesChecker(MultiPartParser& multiparser, unordered_map<string, variant<string, vector<string>>>& validFields); 
        void validateFieldValues();
};
