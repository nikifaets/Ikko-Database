#pragma once
#include "../Record.h"
#include <stdlib.h>

class RecordInt : public Record{

    long long value = 0;
    Type type = Int;
    
    public:

    RecordInt(int val);
    RecordInt(std::string val);
    RecordInt();
    void parse(std::string value);
    long long get_value() const;
    std::string to_string();
    Type get_type() const;

    bool operator ==(const Record& other) const;

};