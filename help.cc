#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <unordered_map>

struct Information {
    std::string validated;
    std::variant<std::string, std::vector<std::string>> value; // Supports both string and array
};

struct EntityData {
    std::string entity;
    Information information;
};

int main() {
    // Example usage
    EntityData entity1 = {"User1", {"true", "SingleStringValue"}};
    EntityData entity2 = {"User2", {"false", std::vector<std::string>{"value1", "value2", "value3"}}};

    // Access values
    std::cout << "Entity: " << entity1.entity << "\nValidated: " << entity1.information.validated
              << "\nValue: " << std::get<std::string>(entity1.information.value) << "\n\n";

    std::cout << "Entity: " << entity2.entity << "\nValidated: " << entity2.information.validated
              << "\nValues: ";
    
    for (const auto& val : std::get<std::vector<std::string>>(entity2.information.value)) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
