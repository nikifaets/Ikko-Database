#pragma once
#include "../Record.h"
#include <stdlib.h>

class RecordInt : private Record{

    long long value;
    const std::string type_name = "Int";

    public:

    void parse(std::string value);
    long long get_value();


};