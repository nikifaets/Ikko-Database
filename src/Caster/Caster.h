#pragma once

#include "../Record/Record.h"

class Caster{

    bool is_number(std::string val);
    bool is_double(std::string val);

    public:
    
    Record* type_to_rec(Type type);
    Record* string_to_rec(std::string val);

};