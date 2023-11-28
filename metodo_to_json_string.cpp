#include <iostream>
#include <vector>
#include <variant>
#include <json.hpp>

class Variant {
public:
    using Value = std::variant<int, double, char, std::string, std::vector<Variant>, std::function<void()>>;
    using Json = nlohmann::json;
    Variant(const Value& value) : data(value) {}

    Json to_json_string() const {
        struct Visitor {
            Json operator()(int value) const { return value; }
            Json operator()(double value) const { return value; }
            Json operator()(char value) const { return std::string(1, value); }
            Json operator()(const std::string& value) const { return value; }
            Json operator()(const std::vector<Variant>& value) const {
                Json array = Json::array();
                for (const auto& element : value) {
                    array.push_back(element.to_json_string());
                }
                return array;
            }
            Json operator()(const std::function<void()>&) const {
                return "Procedimiento";
            }
        };

        return std::visit(Visitor(), data);
    }
private:
    Value data;
};

int main() {
    Variant v1 = 42;
    Variant v2 = 3.14;
    Variant v3 = 'A';
    Variant v4 = "Hola, Mundo!";
    Variant v5 = std::vector<Variant>{1, 2, 3};
    Variant v6 = []() { std::cout << "Hola desde el procedimiento." << std::endl; };

    std::string jsonStr = v5.to_json_string().dump();
    std::cout << jsonStr << std::endl;

    return 0;
}

