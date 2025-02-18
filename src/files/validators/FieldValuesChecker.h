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

        void isValidEntity() {
            string entityValue;
            if (auto* entityPtr = get_if<string>(&this->validFields["entity"])) {
                entityValue = *entityPtr;  // ✅ Safe extraction
            } else {
                throw invalid_argument("Entity must be a string!");
            }

            bool isValid = validEntities.find(entityValue) != validEntities.end();
            if(!isValid) throw invalid_argument("Invalid entity type! Allowed values: " + entitiesAsString);
        }
        void isValidFileFormat(const std::string& filename) {
            // Find the last dot to extract extension
            size_t dotIndex = filename.rfind('.');
            if (dotIndex == string::npos)  throw invalid_argument("Invalid file format");

            std::string extension = filename.substr(dotIndex);
            bool isValid = validFileFormats.find(extension) != validFileFormats.end();
            if(!isValid) throw invalid_argument("Invalid file format");
        } 
        void validateFileFormats(){
            if (auto* filesPtr = get_if<vector<string>>(&this->validFields["files"])) {
                if (filesPtr->empty()) throw invalid_argument("Files cannot be empty");
        
                for(const string& file : *filesPtr) {
                    this->isValidFileFormat(file);
                }
            } else {
                throw invalid_argument("Files must be an array of strings!");
            }
        }

    public:
        FieldValuesChecker(MultiPartParser& multiparser, unordered_map<string, variant<string, vector<string>>>& validFields) 
            : ExistingFieldsChecker(multiparser, validFields) {}
        void validateFieldValues() {
            this->isValidEntity();
            this->validateFileFormats();
        }
};
