#include "Tester.h"
#include "../Database/Database.h"
#include "../Record/RecordDouble/RecordDouble.h"
#include "../Record/RecordInt/RecordInt.h"
#include "../Table/Row/Row.h"
#include <iostream>

void Tester::test_load_database(){

    Database database;
    database.show_tables();
}

void Tester::test_load_table(std::string table_name){

    Database database;
    
    Table table = database.load_table(table_name);


    std::vector<Row> rows = table.get_rows();
    for(int i=0; i<rows.size(); i++){

        std::cout << rows[i].to_string() << std::endl;
    }

    table.save_table(Database::TABLES_LOCATION);
} 

void Tester::test_import_table(std::string filename){

    Database database;

    database.show_tables();
    database.import_table(filename);
    database.show_tables();


}

void Tester::test_export_table(std::string name, std::string filename){

    Database database;
    database.show_tables();
    std::cout << "Exporting table " + name + " into file \n" + filename << std::endl;
    database.export_table(name, filename);
}

void Tester::test_select_rows(std::string name, int col, Record* val){

    std::cout << "Search " + val->to_string() << std::endl;

    Database database;
    database.select_rows(name, col, val);
}

void Tester::test_add_empty_col(std::string tab_name, std::string col_name, Type type){

    Database database;

    std::cout << "Adding column to table " + tab_name + ": " << std::endl;
    database.print_table(tab_name);
    database.add_empty_column(tab_name, col_name, type);
    database.print_table(tab_name);

    std::cout << "Printing the same table from new database object:" << std::endl;
    Database database_new;
    database_new.print_table(tab_name);

}