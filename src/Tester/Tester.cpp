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

void Tester::test_import_table(std::string table_name){

    Database database;

    Table table = database.load_table(table_name);

    std::cout << "Number of columns in the table: " << std::endl;
    table.print_types();
    Record* rec1 = new RecordInt("15");
    Record* rec2 = new RecordInt(177);
    Record* rec3 = new RecordDouble("14.22");

    std::vector<Record*> records1 = {rec1, rec2, rec3};
    std::vector<Record*> records2 = {rec3, rec2, rec1};

    Row row(records1);

    table.add_row(records1);
    //table.save_table(Database::TABLES_LOCATION);
    //add some rows

}