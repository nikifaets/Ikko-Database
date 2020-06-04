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
    int name_to_filename(std::string name);
    void write();
    
    public:

    Table load_table(std::string name);

    Database();
    void show_tables();
    void import_table(std::string filename);
    void export_table(std::string name, std::string filename);
    void describe_table(std::string name);
    void rename_table(std::string name, std::string new_name);
    void print_table(std::string name);
    void select_rows(std::string name, int col, Record* val);
    void add_empty_column(std::string table_name, std::string col_name, Type type);
};