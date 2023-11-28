#include <iostream>
#include <vector>
#include <variant>

class Variant {
public:
    using Value = std::variant<int, double, char, std::string, std::vector<Variant>, void (*)()>;

    Variant(const Value& value) : data(value) {}

    std::string to_string() const {
        struct Visitor {
            std::string operator()(int value) const { return std::to_string(value); }
            std::string operator()(double value) const { return std::to_string(value); }
            std::string operator()(char value) const { return std::string(1, value); }
            std::string operator()(const std::string& value) const { return value; }
            std::string operator()(const std::vector<Variant>& value) const {
                std::string result = "[";
