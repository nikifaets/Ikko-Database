#pragma once
#include "Record.h"

class RecordNumber : public Record{

    public:

    virtual bool operator == (const Record& other)const  = 0;
    virtual RecordNumber* operator + (const RecordNumber& other) = 0;
    virtual RecordNumber* operator *(const RecordNumber& other) = 0;
    virtual bool operator > (const RecordNumber& other) const = 0;
    virtual bool operator < (const RecordNumber& other) const = 0;
};