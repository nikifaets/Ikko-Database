#pragma once
#include "../RecordNumber.h"
#include "../Record.h"
#include <stdlib.h>

class RecordInt : public RecordNumber{

    long long value = 0;
    Type type = Int;
    
    public:

    RecordInt(int val);
    RecordInt(std::string val);
    RecordInt();
    void parse(std::string value);
    long long get_value() const;
    std::string to_string() const;
    std::string to_present_string() const;
    Type get_type() const;

    bool operator ==(const Record& other) const;
    RecordNumber* operator + (const RecordNumber& other);
    RecordNumber* operator *(const RecordNumber& other);
    bool operator > (const RecordNumber& other) const;
    bool operator < (const RecordNumber& other) const;
};