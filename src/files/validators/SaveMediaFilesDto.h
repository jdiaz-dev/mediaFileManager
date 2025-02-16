#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <stdexcept>

using namespace std;
// using namespace drogon;

class SaveMediaFilesDto {
    private:
        static const unordered_set<string> validEntities;
        static const string entitiesAsString;

        static bool isValidEntity(const string& entity) {
            return validEntities.find(entity) != validEntities.end();
        }
        string entity;
        vector<string> files;
    public:
        SaveMediaFilesDto(const string& entity, const vector<string>& files) 
            : entity(entity), files(files) {}
        void validate() const {
            if (!isValidEntity(entity)) {
                throw invalid_argument("Invalid entity type! Allowed values: " + entitiesAsString);
            }
            if (files.empty()) {
                throw invalid_argument("Files array cannot be empty!");
            }
        }
};
