/* #include "SaveMediaFilesDto.h"

using namespace std;

//it is possible to define private members in a .cc file
const unordered_set<string> SaveMediaFilesDto::validEntities = {"avatars", "patientFiles", "patientProgressImages", "chats"};
const string SaveMediaFilesDto::entitiesAsString = []() {  //anonymous lambda function, used to compute the value at compile-time.
    ostringstream oss;
    for (const auto& value : SaveMediaFilesDto::validEntities) {
        if (oss.tellp() > 0) { oss << ", "; }  // Add comma separator
        oss << value;
    }
    return oss.str();
}();
 */