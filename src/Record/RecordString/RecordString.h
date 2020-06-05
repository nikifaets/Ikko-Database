#pragma once

#include "../Record.h"

class RecordString : public Record{

    std::string value;
    //raw string is in c++ format
    std::string value_raw;
    Type type = String;

    public:

    RecordString(std::string val);
    RecordString();
    
    std::string get_value() const;
    void parse(std::string val);
    std::string to_string();
    std::string to_present_string();
    Type get_type() const;

    bool operator ==(const Record& other) const;
    
};