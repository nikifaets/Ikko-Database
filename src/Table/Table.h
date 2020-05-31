#pragma once

#include "Row/Row.h"

class Table{

    std::string name;
    std::vector <Row> rows;
    std::vector<Type> row_types;
    std::vector<std::string> col_names;
    void parse_line(std::string line);
    std::string table_name;
    bool validate_row(Row row);
    std::string types_to_str();
    std::string col_names_to_str();

    public:

    Table(std::string name);
    Table();
    std::vector<Row> get_rows();
    void read_table(std::string filename);
    void save_table(std::string filename);
    std::string get_name();
    void set_name(std::string new_name);
    void print_types();
    std::vector<Row> find_rows_by_value(int column, Record* val);

};