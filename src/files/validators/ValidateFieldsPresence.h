#include <drogon/MultiPart.h>

using namespace std;

class ValidateFieldsPresence {
    private: 
        MultiPartParser multiparser;
        unordered_map<string, bool> fieldsToValidate;
    public:
        ValidateFieldsPresence(MultiPartParser& multiparser, unordered_map<string, bool>& fieldsToValidate) : multiparser(multiparser), fieldsToValidate(fieldsToValidate) {}

        bool existFields(){

            for (const auto& field : this->fieldsToValidate) {  // `pair` is a reference, so we can modify `pair.second`
                    field.first;  // Update the value
                    std::cout << "Updated - " << field.first << ": " << field.second << std::endl;
            }
            return false;
        }


};