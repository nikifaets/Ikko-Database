#pragma once

#include "../Record.h"

class RecordInvalid: public Record{

    Type type = Invalid;

    public:

    Type get_type();
    std::string to_string() const;
    std::string to_present_string() const;
    void parse(std::string value);
    virtual bool operator == (const Record& other) const;
};