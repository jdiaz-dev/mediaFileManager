#include <stdexcept>
#include <drogon/MultiPart.h>

using namespace std;

class ExistingFieldsChecker {
    private: 
        MultiPartParser multiparser;
        unordered_map<string, bool> fieldsToValidate;
        void initializeValidatedFields(){
            for (auto& field : this->validFields) {
                this->fieldsToValidate[field.first] = false;
            }
        }
        void analyzeInParameters(){
            auto parameters = multiparser.getParameters();
            for (auto& field : this->fieldsToValidate) {
                if(parameters.find(field.first) != parameters.end()){
                    field.second = true;
                    this->validFields[field.first] = parameters[field.first];
                }
            }
        }
        void analyzeInFiles() {
        for (const auto &file : this->multiparser.getFiles()) {
                std::string keyName = file.getItemName();
                std::string fileName = file.getFileName();

                if (this->fieldsToValidate.find(keyName) != this->fieldsToValidate.end()) {
                    this->fieldsToValidate[keyName] = true;

                    // ✅ Extracting a vector<string> safely
                    if (auto* fileList = get_if<vector<string>>(&this->validFields.find(keyName)->second)) {
                        fileList->push_back(fileName);  
                    } 
                } 
            }
        }
        void validateFields(){
            for (const auto& field : this->fieldsToValidate) {
                if(field.second == false){
                    throw invalid_argument("Field " + field.first + " is required");
                }
            }
        }
    public:
        unordered_map<string, variant<string, vector<string>>> validFields;
        ExistingFieldsChecker(MultiPartParser& multiparser, unordered_map<string, variant<string, vector<string>>>& validFields) : multiparser(multiparser), validFields(validFields) {}

        void validate(){
            initializeValidatedFields();
            analyzeInParameters();
            analyzeInFiles();
            validateFields();
        }
};

    

    