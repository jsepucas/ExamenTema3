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

int main() {
    Entorno gameEnvironment;

    gameEnvironment.setVariable("VidaJugador", 100);
    gameEnvironment.setVariable("Puntuacion", 0);
    gameEnvironment.setVariable("NombreNivel", string("Casa Abandonada"));

    try {
        cout << "Vida del Jugador: " << gameEnvironment.getVariable<int>("VidaJugador") << endl;
        cout << "Puntuacion: " << gameEnvironment.getVariable<int>("Puntuacion") << endl;
        cout << "Nombre del Nivel: " << gameEnvironment.getVariable<string>("NombreNivel") << endl;
    } catch (const runtime_error& e) {






};