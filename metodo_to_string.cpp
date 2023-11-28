#include <iostream>
#include <vector>
#include <variant>
#include <functional>

class Variant {
public:
    using Value = std::variant<int, double, char, std::string, std::vector<Variant>, std::function<void()>>;

    Variant(const Value& value) : data(value) {}

    Variant(int i) {

    }

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
            std::string operator()(const std::function<void()>&) const {
                return "Procedimiento";
            }
        };

        return std::visit(Visitor(), data);
    }

private:
    Value data;
};

int main() {
    Variant v1 = 11;
    Variant v2 = 3.141592;
    Variant v3 = static_cast<const Variant::Value &>('A');
    Variant v4 = (Variant &&) "Hola,mundo!";
    Variant v5 = static_cast<const Variant::Value &>(std::vector<Variant>{1, 2, 3});

    std::cout << v1.to_string() << std::endl;
    std::cout << v2.to_string() << std::endl;
    std::cout << v3.to_string() << std::endl;
    std::cout << v4.to_string() << std::endl;
    std::cout << v5.to_string() << std::endl;

    return 0;
}

