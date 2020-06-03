#pragma once
#include "../Table/Table.h"

class Database{

    std::vector<std::string> table_names;
    bool is_table_present(std::string name);
    void refresh();
    
    public:

    Table load_table(std::string name);

    Database();
    void show_tables();
    void import(std::string filename);
    void export_table(std::string name, std::string filename);
    void describe_table(std::string name);
    void rename_table(std::string name, std::string new_name);
};