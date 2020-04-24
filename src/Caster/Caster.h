#pragma once

#include "../Record/Record.h"

class Caster{

    public:
    
    static Record* type_to_rec(Type type);
    static Record* string_to_rec(std::string val);

};