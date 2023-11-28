#include <iostream>
#include <vector>
#include <variant>
#include <nlohmann/json.hpp>

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

