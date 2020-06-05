#pragma once

#include "../Record.h"

class RecordInvalid: public Record{

    Type type = Invalid;

    public:

    Type get_type();
    std::string to_string();
    std::string to_present_string();
    void parse(std::string value);
    virtual bool operator == (const Record& other) const;
};