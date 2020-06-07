#pragma once

#include "../Record.h"
#include "../RecordNumber.h"

class RecordDouble : public RecordNumber{

    const double COMP_EPS = 1e-7;
    Type type = Double;
    double value = 0;

    public:

    RecordDouble(double val);
    RecordDouble(std::string val);
    RecordDouble();
    void parse(std::string value);
    double get_value() const;
    std::string to_string() const;
    std::string to_present_string() const;
    Type get_type() const;

    virtual bool operator ==(const Record& other) const;
    RecordNumber* operator + (const RecordNumber& other);
    RecordNumber* operator *(const RecordNumber& other);
    bool operator > (const RecordNumber& other) const;
    bool operator < (const RecordNumber& other) const;
};