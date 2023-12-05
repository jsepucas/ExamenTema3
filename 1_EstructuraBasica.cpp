#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <variant>

using namespace std;

//Creo una clase Entorno para gestionar las variables

class Entorno {
public:
    Entorno () = default;

    //Elimino el constructor de copia y el operador de asignación para evitar copias que no quiero

    Entorno (const Entorno&) = delete;
    Entorno& operator=(const Entorno&) = delete;

    //Creo una función para asignar variables

    void setVariable(const string& nombre, const variant<int, double, string>& valor) {
        simbolos[nombre] = valor;

    }

    template<typename T>
    T getVariable(const string& name) const {
        auto it = simbolos.find(name);
        if (it != simbolos.end()) {
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
// Establezco las distintas variables
    gameEnvironment.setVariable("VidaJugador", 500);
    gameEnvironment.setVariable("Puntuacion", 10);
    gameEnvironment.setVariable("NombreNivel", string("Casa Abandonada"));

//Try catch para capturar los errores
    try {

        //Valor de las variables
        cout << "Vida del Jugador: " << gameEnvironment.getVariable<int>("VidaJugador") << endl;
        cout << "Puntuacion: " << gameEnvironment.getVariable<int>("Puntuacion") << endl;
        cout << "Nombre del Nivel: " << gameEnvironment.getVariable<string>("NombreNivel") << endl;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}








