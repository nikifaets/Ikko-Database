#pragma once

#include "Row/Row.h"

class Table{

    std::string name;
    std::vector <Row> rows;
    std::vector<Type> col_types;
    std::vector<std::string> col_names;
    void parse_line(std::string line);
    std::string table_name;
    bool validate_row(Row row);
    std::string types_to_str();
    std::string col_names_to_str();
    bool loaded = true;

    public:

    Table(std::string filename);
    Table();
    std::vector<Row> get_rows();
    void read_table(std::string filename);
    void save_table(std::string filename);
    bool is_loaded_correctly();
    std::string get_name();
    void set_name(std::string new_name);
    void print_types();
    std::vector<int> find_rows_by_value(int column, Record* val);
    void add_row(Row row);
    void add_empty_column(std::string name, Type type);
};