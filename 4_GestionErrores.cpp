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
            iter->second.first = value; // Actualizo el valor de la variable
        }
    }

    Value getVariable(const string& name) const {
        auto it = simbolos.find(name);
        if (it == simbolos.end()) {
            throw runtime_error("La variable del juego '" + name + "' no existe");
        }
        return it->second.first;
    }

private:
    map<string, pair<Value, bool>> simbolos; // El booleano indica si es de solo lectura
};

int main() {
    Entorno gameEnv;

    try {
        gameEnv.setVariable("maxSalud", 100, true); // Constante del juego
        gameEnv.setVariable("JugadorSalud", 100);   // Variable del juego
        gameEnv.setVariable("NombreJugador", string("Hero")); // Nombre del jugador
        gameEnv.setVariable("maxSalud", 200); // Intento fallido de modificar una constante

        cout << "Salud Máxima: " << get<int>(gameEnv.getVariable("maxSalud")) << endl;
        cout << "Salud del Jugador: " << get<int>(gameEnv.getVariable("JugadorSalud")) << endl;
        cout << "Nombre del Jugador: " << get<string>(gameEnv.getVariable("NombreJugador")) << endl;
    } catch (const runtime_error& e) {
        cerr << "Ha habido un error en el juego: " << e.what() << endl;
    }




    }
