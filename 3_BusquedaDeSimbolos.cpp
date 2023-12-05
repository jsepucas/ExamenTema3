#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <optional>

using namespace std;

class Entorno {
public:
    using Value = variant<int, double, string>;

    Entorno() = default;

    Entorno(const Entorno&) = delete;
    Entorno& operator=(const Entorno&) = delete;

    void setVariable(const string& name, const Value& value) {
        simbolos[name] = value;
    }

    optional<Value> lookup(const string& name) const {
        auto it = simbolos.find(name);
        if (it != simbolos.end()) {
            return it->second;
        } else {
            return nullopt;
        }
    }

private:
    map<string, Value> simbolos;
};
void printVariable(const optional<Entorno::Value>& value, const string& name) {
    if (value) {
        visit([&name](const auto& v) { cout << "Valor de '" << name << "': " << v << endl; }, *value);
    } else {
        cout << "La variable '" << name << "' no existe." << endl;
    }
}



