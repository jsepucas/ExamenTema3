#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <stdexcept>

using namespace std;

class Entorno {
public:
    using Value = variant<int, double, string>;

    Entorno() = default;

    Entorno(const Entorno&) = delete;
    Entorno& operator=(const Entorno&) = delete;

    void setVariable(const string& name, const Value& value, bool readOnly = false) {
        auto [iter, success] = simbolos.insert({name, make_pair(value, readOnly)});
        if (!success && iter->second.second) {
            throw runtime_error("No se puede modificar la constante del juego '" + name + "'");
        } else if (!success) {
            iter->second.first = value;
        }
    }

    template<typename T>
    T getVariableAs(const string& name) const {
        auto it = simbolos.find(name);
        if (it == simbolos.end()) {
            throw runtime_error("La variable del juego '" + name + "' no existe");
        }
        try {
            return get<T>(it->second.first);
        } catch (const bad_variant_access&) {
            throw runtime_error("Tipo incorrecto para la variable '" + name + "'");
        }
    }
private:
    map<string, pair<Value, bool>> simbolos; // Almacenar variables con una marca de solo lectura
};

int main() {
    Entorno gameEnv;

    gameEnv.setVariable("Dificultad", string("Dificil"));
    gameEnv.setVariable("Salud", 200);
    gameEnv.setVariable("Puntos", 10000);
    private:
    map<string, pair<Value, bool>> simbolos; // Almacenar variables con una marca de solo lectura
};

int main() {
    Entorno gameEnv;

    gameEnv.setVariable("Dificultad", string("Normal"));
    gameEnv.setVariable("Salud", 100);
    gameEnv.setVariable("Puntos", 5000);

