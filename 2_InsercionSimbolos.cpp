#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <variant>

using namespace std;

class Entorno {
public:
    Entorno() = default;

    Entorno(const Entorno&) = delete;
    Entorno& operator=(const Entorno&) = delete;

    bool insert(const std::string& name, const std::variant<int, double, std::string>& value) {
        auto result = simbolos.insert({name, value});
        return result.second;
    }
    void setVariable(const std::string& name, const std::variant<int, double, std::string>& value) {
        simbolos[name] = value;
    }

    template<typename T>
    T getVariable(const std::string& name) const {
        auto it = simbolos.find(name);
        if (it != simbolos.end()) {
try {
                return std::get<T>(it->second);
            } catch (const std::bad_variant_access&) {
                throw std::runtime_error("El Tipo de variable es incorrecto para " + name);
            }
        } else {
            throw std::runtime_error("Variable no fue encontrada: " + name);
        }

    }
private:
    std::map<std::string, std::variant<int, double, std::string>> simbolos;
};

int main() {
    Entorno gameEnvironment;


    bool inserted = gameEnvironment.insert("VidaJugador", 100);
   cout << "'vidaJugador' ha sido insertada? " << (inserted ? "Si" : "No") << std::endl;




