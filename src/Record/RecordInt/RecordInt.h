#pragma once
#include "../Record.h"
#include <stdlib.h>

class RecordInt : public Record{

    long long value;
    const Type rec_type = Int;

    public:

    RecordInt(std::string val);
    RecordInt();
    void parse(std::string value);
    long long get_value();


};