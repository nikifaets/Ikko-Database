#pragma once

#include "../Record.h"

class RecordDouble : public Record{

    const double COMP_EPS = 1e-7;
    Type type = Double;
    double value = 0;

    public:

    RecordDouble(double val);
    RecordDouble(std::string val);
    RecordDouble();
    void parse(std::string value);
    double get_value() const;
    std::string to_string();
    Type get_type() const;

    virtual bool operator ==(const Record& other) const;
};