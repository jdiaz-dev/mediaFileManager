#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <stdexcept>
#include <drogon/HttpRequest.h>
#include <drogon/utils/Utilities.h>

using namespace std;
// using namespace drogon;

class SaveMediaFilesDto {
    private:
        static const std::unordered_set<std::string> validEntities;
        static const std::string entitiesAsString;

        static bool isValidEntity(const string& entity) {
            return validEntities.find(entity) != validEntities.end();
        }
        string entity;
        vector<string> files;  // Should be an array of file names
    public:
        SaveMediaFilesDto(const string& entity, const vector<string>& files) 
            : entity(entity), files(files) {}
        void verifyValidParameters(const drogon::SafeStringMap<std::string>& parameters) const {
            for (const auto& param : parameters) {
                cout << "param = " << param.first << endl;
                cout << "param = " << param.second << endl;
                /* if (param.first) {
                    throw invalid_argument("Empty parameter value!");
                } */
            }
        }
        void validate() const {
            if (!isValidEntity(entity)) {
                throw invalid_argument("Invalid entity type! Allowed values: " + entitiesAsString);
            }
            if (files.empty()) {
                throw invalid_argument("Files array cannot be empty!");
            }
        }
        void validateFormData(int& parsedRequest){
            if (parsedRequest != 0) {
                LOG_ERROR << "Failed to parse multipart form-data";
                throw invalid_argument("Invalid multipart form-data!");

            }
        }
        
};
