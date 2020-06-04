#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include "../../Record/Record.h"

class Parser{

    static const int MIN_ASCII = 41;
    static std::string read_until_whitespace(std::string str);
    static bool is_separator(char c);
    static const std::unordered_set<char> separators;

    public:

    static bool is_number(std::string val);
    static bool is_double(std::string val);
    static bool is_int(std::string val);
    static bool is_digit(char c);
    static bool validate_type_data(std::vector<std::string>);
    static std::vector<std::string> parse_line_str(std::string line);
    static std::vector <Record*> parse_line(std::string line, std::vector<Type> types);
    static std::vector <Type> parse_type_data(std::string line);
    static bool has_whitespace(std::string str);

};