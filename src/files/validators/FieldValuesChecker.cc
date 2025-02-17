#include "FieldValuesChecker.h"

using namespace std;

//it is possible to define private members in a .cc file
const unordered_set<string> FieldValuesChecker::validEntities = {"avatars", "patientFiles", "patientProgressImages", "chats"};
const unordered_set<string> FieldValuesChecker::validFileFormats = {".jpg", ".png", ".gif", ".bmp", ".jpeg"};
const string FieldValuesChecker::entitiesAsString = []() {  //anonymous lambda function, used to compute the value at compile-time.
    ostringstream oss;
    for (const auto& value : FieldValuesChecker::validEntities) {
        if (oss.tellp() > 0) { oss << ", "; }  // Add comma separator
        oss << value;
    }
    return oss.str();
}();
