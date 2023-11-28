#include <iostream>
#include <vector>
#include <variant>
#include <nlohmann/json.hpp>

class Variant {
public:
    using Value = std::variant<int, double, char, std::string, std::vector<Variant>, std::function<void()>>;
    using Json = nlohmann::json;

