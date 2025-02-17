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
            vector<string> files;
            if (auto* filesPtr = get_if<vector<string>>(&this->validFields["files"])) {
                files = *filesPtr;  // ✅ Safe extraction
            } else {
                throw invalid_argument("Files must be an array of strings!");
            }

            if(files.size() == 0) throw invalid_argument("Files cannot be empty" );

            for (const std::string& file : files) {
                this->isValidFileFormat(file);
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


/* bool isValidFormat(const std::string& filename) {
    // Allowed formats
    const std::set<std::string> validFormats = {".jpg", ".png", ".gif", ".bmp", ".jpeg"};

    // Find the last dot to extract extension
    size_t dotPos = filename.rfind('.');
    if (dotPos == std::string::npos) return false; // No extension found

    std::string extension = filename.substr(dotPos);
    return validFormats.find(extension) != validFormats.end();
}

int main() {
    std::vector<std::string> files = {"image.jpg", "document.pdf", "photo.png", "file.bmp"};

    for (const std::string& file : files) {
        if (isValidFormat(file)) {
            std::cout << file << " is a valid format." << std::endl;
        } else {
            std::cout << file << " is NOT a valid format." << std::endl;
        }
    }

    return 0;
}
 */