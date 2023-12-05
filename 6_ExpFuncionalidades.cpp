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