#pragma once

#include "Row/Row.h"
#include <unordered_set>

class Table{

    std::vector <Row> rows;

    void parse_line(std::string line);
    std::string old_filename;

    public:

    std::vector<Row> get_rows();
    void read_table(std::string filename);
    void save_table(std::string filename);

};