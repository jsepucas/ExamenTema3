#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <optional>

using namespace std;

class Entorno {
public:
    using Value = variant<int, double, string>;

    Entorno() = default;

    Entorno(const Entorno&) = delete;
    Entorno& operator=(const Entorno&) = delete;
