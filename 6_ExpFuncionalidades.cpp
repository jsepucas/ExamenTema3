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

    string isVariableReadOnly(const string& name) const {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            return (it->second.second) ? "Sí" : "No";
        } else {
            throw runtime_error("Variable del juego '" + name + "' no encontrada");
        }
    }

    void clearEnvironment() {
        symbols.clear();
    }

    vector<string> getAllVariables() const {
        std::vector<string> variableList;
        for (const auto& pair : symbols) {
            variableList.push_back(pair.first);
        }
        return variableList;
    }

private:
    std::map<std::string, std::pair<Value, bool>> symbols;
};

int main() {
    Environment gameEnv;

    gameEnv.setVariable("playerHealth", 200);
    gameEnv.setVariable("playerName", std::string("Mario"));
    gameEnv.setVariable("maxHealth", 300, true);

    cout << "Salud del Jugador: " << gameEnv.getVariableAs<int>("playerHealth") << endl;
    cout << "Nombre del Jugador: " << gameEnv.getVariableAs<std::string>("playerName") << endl;

    string varName = "maxHealth";
    cout << "Es '" << varName << "' de solo lectura? " << gameEnv.isVariableReadOnly(varName) << endl;

    try {
        gameEnv.setVariable("maxHealth", 500);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
    gameEnv.removeVariable("NombreJugador");

    string deletedVarName = "playerName";
    cout << "Existe '" << deletedVarName << "' en el entorno? " << (gameEnv.hasVariable(deletedVarName) ? "Sí" : "No") << endl;





