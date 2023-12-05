#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <stdexcept>
#include<vector>

using namespace std;

class Entorno {
public:
    using Value = variant<int, double, std::string>;

    Entorno() = default;

    Entorno(const Entorno&) = delete;
    Entorno& operator=(const Entorno&) = delete;

    void setVariable(const string& name, const Value& value, bool readOnly = false) {
        auto [iter, success] = symbols.insert({name, make_pair(value, readOnly)});
        if (!success && iter->second.second) {
            throw runtime_error("No se puede modificar la constante del juego '" + name + "'");
        } else if (!success) {
            iter->second.first = value;
        }
    }

    template<typename T>
    T getVariableAs(const std::string& name) const {
        auto it = symbols.find(name);
        if (it == symbols.end()) {
            throw std::runtime_error("La variable del juego '" + name + "' no existe");
        }

        try {
            return get<T>(it->second.first);
        } catch (const bad_variant_access&) {
            throw runtime_error("Tipo incorrecto para la variable '" + name + "'");
        }
    }

    void removeVariable(const std::string& name) {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            symbols.erase(it);
        }
    }
    bool hasVariable(const std::string& name) const {
        return symbols.find(name) != symbols.end();
    }

