#pragma once

#include "Row/Row.h"
#include <unordered_set>

class Table{

    std::vector <Row> rows;
    std::vector<Type> row_types;
    void parse_line(std::string line);
    std::string table_name;
    bool validate_row(Row row);
    std::string types_to_str();

    public:

    std::vector<Row> get_rows();
    void read_table(std::string filename);
    void save_table(std::string filename);

};