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
                for (const auto& element : value) {
                    result += element.to_string() + ", ";
                }
                if (!value.empty()) {
                    result.erase(result.end() - 2, result.end());
                }
                result += "]";
                return result;
            }
            std::string operator()(void (*value)()) const {
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
    Variant v6 = +[]() { std::cout << "Hola desde el procedimiento." << std::endl; };

    std::cout << v1.to_string() << std::endl;
    std::cout << v2.to_string() << std::endl;
    std::cout << v3.to_string() << std::endl;
    std::cout << v4.to_string() << std::endl;
    std::cout << v5.to_string() << std::endl;
    v6.to_string();

    return 0;
}

