#pragma once
#include "../Table/Table.h"

class Database{

    friend class Tester;

    //locations, compared to build directory
    static const std::string DATABASE_LOCATION;
    static const std::string TABLES_LOCATION;

    std::vector<std::string> table_names;
    std::vector<std::string> table_filenames;

    bool is_table_present(std::string name);
    std::string name_to_filename(std::string name);
    Table create_table(std::string name, std::vector<std::string> names, std::vector<Type> types);
    
    public:

    Table load_table(std::string name);

    Database();
    
    void write(std::string path = DATABASE_LOCATION);
    void show_tables();
    void import_table(std::string filename);
    void export_table(std::string name, std::string filename);
    void describe_table(std::string name);
    void rename_table(std::string name, std::string new_name);
    void print_table(std::string name);
    void select_rows(std::string name, int col, Record* val);
    void add_empty_column(std::string table_name, std::string col_name, Type type);
    void update_column(std::string table_name, int search_col, Record* search_val, int target_col, Record* target_val);
    void insert(std::string table_name, Row row);
    void delete_rows(std::string table_name, int search_col, Record* val);
    void count_cols(std::string table_name, int col_idx, Record* val);
    void innerjoin(std::string table1, int col1, std::string table2, int col2);
    void aggregate(std::string table_name, int search_col, Record* search_val, int target_col, std::string operation);

};