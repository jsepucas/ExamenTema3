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

    Environment(const Entorno&) = delete;
    Entorno& operator=(const Entorno&) = delete;