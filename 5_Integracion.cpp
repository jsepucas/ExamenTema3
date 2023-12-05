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
private:
    Value value;
};

class Entorno {
public:

    void addSymbol(const string& symbol, const Variant::Value& value) {
        symbolTable[symbol] = value;
    }

    Variant::Value getSymbolValue(const string& symbol) const {
        auto it = symbolTable.find(symbol);
        if (it != symbolTable.end()) {
            return it->second;
        } else {
            cerr << "Error: El simbolo '" << symbol << "' no esta definido." << endl;
            return Variant::Value{};
        }
    }

private:
    std::map<std::string, Variant::Value> symbolTable;
};

int main() {
    Environment myEnvironment;

    myEnvironment.addSymbol("x", 42);
    myEnvironment.addSymbol("y", 2.17);
    myEnvironment.addSymbol("Nombre", "Juan");

    Variant::Value valueX = myEnvironment.getSymbolValue("x");
    Variant::Value valueY = myEnvironment.getSymbolValue("y");
    Variant::Value valueName = myEnvironment.getSymbolValue("Nombre");


