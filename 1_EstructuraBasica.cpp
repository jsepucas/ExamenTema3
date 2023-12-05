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




};