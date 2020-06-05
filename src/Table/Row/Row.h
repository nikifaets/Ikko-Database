#pragma once
#include "../../Record/Record.h"
#include <vector>

class Row{

    std::vector<Record*> records;

    public:

    Row();
    Row(std::vector<Record*> recs);
    void add_record(Record* rec);
    void add_empty_record(Type type);
    void add_record(std::string val);
    std::vector<Record*> get_records();
    std::string to_string();
    void change_rec(int col_idx, Record* rec);

};