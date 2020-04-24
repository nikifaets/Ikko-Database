#pragma once

#include <string>
#include <vector>
#include "../../Record/Record.h"

class Parser{

    static const int MIN_ASCII = 41;
    static std::string read_until_whitespace(std::string str);

    public:

    static bool is_number(std::string val);
    static bool is_double(std::string val);
    static bool is_digit(char c);
    static std::vector <Record*> parse_line(std::string line);

};