#include "ExistingFieldsChecker.h"

void ExistingFieldsChecker::initializeValidatedFields(){
    for (auto& field : this->validFields) {
        this->fieldsToValidate[field.first] = false;
    }
}
void ExistingFieldsChecker::analyzeInParameters(){
    auto parameters = multiparser.getParameters();
    for (auto& field : this->fieldsToValidate) {
        if(parameters.find(field.first) != parameters.end()){
            field.second = true;
            this->validFields[field.first] = parameters[field.first];
        }
    }
}
void ExistingFieldsChecker::analyzeInFiles() {
    for (const auto &file : this->multiparser.getFiles()) {
        string keyName = file.getItemName();
        string fileName = file.getFileName();
        if (this->fieldsToValidate.find(keyName) != this->fieldsToValidate.end()) {
            this->fieldsToValidate[keyName] = true;
            //  Extracting a vector<string> safely
            if (auto* fileList = get_if<vector<string>>(&this->validFields.find(keyName)->second)) {
                fileList->push_back(fileName);  
            } 
        } 
    }
}

ExistingFieldsChecker::ExistingFieldsChecker(MultiPartParser& multiparser, unordered_map<string, variant<string, vector<string>>>& validFields) : multiparser(multiparser), validFields(validFields) {}

void ExistingFieldsChecker::checkFields(){
    for (const auto& field : this->fieldsToValidate) {
        if(field.second == false){
            throw invalid_argument("Field " + field.first + " is required");
        }
    }
}
void ExistingFieldsChecker::validateFields(){
    initializeValidatedFields();
    analyzeInParameters();
    analyzeInFiles();
    checkFields();
}
