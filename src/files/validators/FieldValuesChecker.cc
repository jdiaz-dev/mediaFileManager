#include <string>
#include <variant>
#include <vector>
#include "FieldValuesChecker.h"

using namespace std;

const unordered_set<string> FieldValuesChecker::validActions = {"compress", "store"};
const unordered_set<string> FieldValuesChecker::validFileFormats = {".pdf", ".jpg", ".png", ".gif", ".bmp", ".jpeg"};
const string FieldValuesChecker::actionsAsString = []() {  //anonymous lambda function, used to compute the value at compile-time.
    ostringstream oss;
    for (const auto& value : FieldValuesChecker::validActions) {
        if (oss.tellp() > 0) { oss << ", "; }  // Add comma separator
        oss << value;
    }
    return oss.str();
}();
void FieldValuesChecker::isValidAction() {
    string actionValue;
    if (auto* entityPtr = get_if<string>(&this->validFields["action"])) {
        actionValue = *entityPtr;  // ✅ Safe extraction
    } else {
        throw invalid_argument("Action must be a string!");
    }
    bool isValid = validActions.find(actionValue) != validActions.end();
    if(!isValid) throw invalid_argument("Invalid action type! Allowed values: " + actionsAsString);
}
void FieldValuesChecker::isValidFileFormat(const string& filename) {
    // Find the last dot to extract extension
    size_t dotIndex = filename.rfind('.');
    if (dotIndex == string::npos)  throw invalid_argument("Invalid file format");
    string extension = filename.substr(dotIndex);
    bool isValid = validFileFormats.find(extension) != validFileFormats.end();
    if(!isValid) throw invalid_argument("Invalid file format");
} 
void FieldValuesChecker::validateFileFormats(){
    if (auto* filesPtr = get_if<vector<string>>(&this->validFields["files"])) {
        if (filesPtr->empty()) throw invalid_argument("Files cannot be empty");

        for(const string& file : *filesPtr) {
            this->isValidFileFormat(file);
        }
    } else {
        throw invalid_argument("Files must be an array of strings!");
    }
}

FieldValuesChecker::FieldValuesChecker(unordered_map<string, variant<string, vector<string>>>& validFields) 
    : validFields(validFields) {}
void FieldValuesChecker::validateFieldValues() {
    this->isValidAction();
    this->validateFileFormats();
}