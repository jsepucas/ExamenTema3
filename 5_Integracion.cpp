#include <iostream>
#include <map>
#include <string>
#include <variant>

using namespace std;

class Variant {
public:

    using Value = std::variant<int, double, std::string>;

    Variant(const Value& val) : value(val) {}

    Value getValue() const {
        return value;
    }

    void printValue() const {
        visit([](const auto& v) { std::cout << v; }, value);
        cout << endl;
    }
