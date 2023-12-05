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
