#pragma once
#include <string>
#include "../Record/Record.h"


class Tester{

    public:

    void test_load_database();
    void test_load_table(std::string table_name);
    void test_import_table(std::string table_name);
    void test_export_table(std::string table_name, std::string filename);
    void test_select_rows(std::string name, int col, Record* val);
    void test_add_empty_col(std::string tab_name, std::string col_name, Type type);
    void test_rec_comparison();
    void test_update_rec();
    void test_delete_rows();
    void test_concat();
    void test_innerjoin();
};