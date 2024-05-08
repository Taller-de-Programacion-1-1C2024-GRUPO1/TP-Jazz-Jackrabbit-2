#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../common_src/utils.h"

class Parser {
public:
    Parser();
    std::pair<uint8_t, int> line_to_bytes_parser(const std::string& line);
    ~Parser();
};

#endif
