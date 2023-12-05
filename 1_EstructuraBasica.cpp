#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <variant>

using namespace std;

class Entorno {
public:
    Entorno () = default;

    Entorno (const Entorno&) = delete;
    Entorno& operator=(const Entorno&) = delete;

    void setVariable(const string& nombre, const variant<int, double, string>& valor) {
        simbolos[nombre] = valor;

    }

    template<typename T>
    T getVariable(const string& name) const {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            try {
                return get<T>(it->second);
            } catch (const bad_variant_access&) {
                throw runtime_error("Tipo de variable incorrecto para " + name);
            }

            } else {
        throw runtime_error("La Variable no fue encontrada: " + name);
            }
    }
private:
    map<string, variant<int, double, string>> simbolos;
};




};