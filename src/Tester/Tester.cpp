#include "Tester.h"
#include "../Database/Database.h"
#include "../Record/RecordDouble/RecordDouble.h"
#include "../Record/RecordInt/RecordInt.h"
#include "../Table/Row/Row.h"
#include "../Presenter/Presenter.h"
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

void Tester::test_rec_comparison(){

    Record* r_double1 = new RecordDouble("123.1");
    Record* r_double2 = new RecordDouble("123.1");
    Record* r_empty1 = new RecordDouble(11.1);
    r_empty1->set_empty(true);
    Record* r_empty2 = new RecordDouble(115.2);
    r_empty2->set_empty(true);


    std::cout << "Comparing equal: " << (*r_double1 == *r_double2) << std::endl; 
    std::cout << "comparing empty: " << (*r_empty1 == *r_empty2) << std::endl;
    std::cout << "compare empty with non empty (different) " <<
    (*r_double1 == *r_empty1) << std::endl; 
}

void Tester::test_update_rec(){

    Table table("../test_update");
    
    std::cout << "Table before update: " << std::endl;
    Presenter::show_table(table);

    table.update_column(0, new RecordInt(15), 1, new RecordInt(23));

    std::cout << "Table update: " << std::endl;
    Presenter::show_table(table);

    std::cout << "Test update for different column types: " << std::endl;
    table.update_column(1, new RecordInt(23), 2, new RecordDouble(5.5));
    std::cout << "Table after update:" << std::endl;
    Presenter::show_table(table);

    std::cout << "Validation test: Wrong type" << std::endl;
    table.update_column(0, new RecordDouble(12.2), 1, new RecordInt(100));

    std::cout << "Table after validation test: " << std::endl;
    Presenter::show_table(table);

    std::cout << "Test comparison with Null value" << std::endl;
    table.add_empty_column("Empty", Type::Int);
    Record* empty_rec = new RecordInt(3);
    empty_rec->set_empty(true);

    table.update_column(3, empty_rec, 0, new RecordInt(69));
    std::cout << "After update: " << std::endl;
    Presenter::show_table(table);

}
void Tester::test_delete_rows(){

    Table table("../test_update");
    
    std::cout << "Table before deletion " << std::endl;
    Presenter::show_table(table);

    table.count(0, new RecordInt(15));
    table.delete_rows(0, new RecordInt(15));
    std::cout << "Table after deletion " << std::endl;
    Presenter::show_table(table);
    
}