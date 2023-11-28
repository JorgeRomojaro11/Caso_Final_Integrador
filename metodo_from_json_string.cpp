#include <iostream>
#include <vector>
#include <variant>
#include <nlohmann/json.hpp>

class Variant {
public:
    using Json = nlohmann::json;
    using Value = std::variant<int, double, char, std::string, std::vector<Variant>, std::function<void()>>;

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

    static Variant from_json_string(const std::string& jsonString) {
        Json json = Json::parse(jsonString);

        struct JsonVisitor {
            Variant operator()(int value) const { return value; }
            Variant operator()(double value) const { return value; }
            Variant operator()(const std::string& value) const { return value; }
            Variant operator()(const Json& array) const {
                std::vector<Variant> variantArray;
                for (const auto& element : array) {
                    variantArray.push_back(from_json_string(element.dump()));
                }
                return variantArray;
            }
            Variant operator()(const Json&) const {

                return "Tipo no compatible con Variant";
            }
        };

        return json.get<Variant::Value>().visit(JsonVisitor());
    }

private:
    Value data;
};

int main() {
    std::string jsonString = R"({"key": [1, 2, "hello", 3.14]})";

    Variant v = Variant::from_json_string(jsonString);

    std::cout << v.to_json_string().dump() << std::endl;

    return 0;
}
