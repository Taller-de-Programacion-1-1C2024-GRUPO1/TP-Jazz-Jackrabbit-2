#include "client_parser.h"


Parser::Parser() {}

std::pair<uint8_t, int> Parser::line_to_bytes_parser(const std::string& str) {
    const std::unordered_map<std::string, uint8_t> word_map = {
            {"Atacar", ATACK}, {"Leer", READ}, {"Salir", EXIT}};
    // Buscar la palabra en el mapeo
    auto it = word_map.find(str);
    if (it != word_map.end()) {
        // Devolver el valor correspondiente si se encuentra la palabra
        return {it->second, INVALID};  // Devuelve -1 para indicar que no se especificó el número de
                                       // bytes a leer
    } else {
        // Si la palabra no se encuentra en el mapeo, intentar extraer el número de bytes
        if (str.substr(0, 4) == "Leer") {
            std::istringstream iss(str.substr(5));
            int num_bytes;
            if (iss >> num_bytes) {
                return {0, num_bytes};  // Devolver 0 para indicar Leer y el número de bytes a leer
            }
        }
    }
    // Devolver -1 para indicar que la palabra no se encontró y que no se especificó el número de
    // bytes a leer
    return {INVALID, INVALID};
}

Parser::~Parser() {}
