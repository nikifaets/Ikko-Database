#pragma once
#include "../../Record/Record.h"
#include <vector>

class Row{

    std::vector<Record*> records;

    public:

    void add_record(Record* rec);
    void add_empty_record(Type type);
    void add_record(std::string val);
    std::vector<Record*> get_records();

};