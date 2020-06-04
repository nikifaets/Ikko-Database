#include "Database.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "../Message/Message.h"
#include "../Presenter/Presenter.h"
#include "../Table/Parser/Parser.h"

const std::string Database::DATABASE_LOCATION = "../src/Database/Database";
const std::string Database::TABLES_LOCATION = "../src/Database/Tables";

Database::Database(){

    std::ifstream database(DATABASE_LOCATION);

    //parse all tables' files
    std::string filename;

    while(std::getline(database, filename)){

        Table table(filename);
        if(!table.is_loaded_correctly()) continue;
        table_filenames.push_back(filename);
    }

    for(int i=0; i<table_filenames.size(); i++){

        Table table(table_filenames[i]);
        std::string name = table.get_name();
        table_names.push_back(name);
        
    }

}

Table Database::load_table(std::string name){

    if(!is_table_present(name)){

        Message::FileNotFound(name);
        return Table();
    }

    int name_idx = name_to_filename(name);
    Table table(table_filenames[name_idx]);

    return table;
}

void Database::show_tables(){

    for(int i=0; i<table_names.size(); i++){

        std::cout << table_names[i] << std::endl;
    }
}

void Database::import_table(std::string filename){

    Table table(filename);
    if(!table.is_loaded_correctly()) return;

    std::string name = table.get_name();

    if(is_table_present(name)){

        Message::NameTaken();
        return;
    }    

    std::ofstream database(DATABASE_LOCATION, std::ios::app);
    database << std::endl << filename;
    database.close();

    table_names.push_back(name);
    table_filenames.push_back(filename);

}

void Database::export_table(std::string name, std::string filename){

    if(!is_table_present(name)){

        Message::FileNotFound(name);
        return;
    }

    int name_idx = name_to_filename(name);

    Table table(table_filenames[name_to_filename(name)]);
    table.save_table(filename);
}

bool Database::is_table_present(std::string name){

    std::vector<std::string>::iterator it;
    it = std::find(table_names.begin(), table_names.end(), name);

    return it != table_names.end();
}

int Database::name_to_filename(std::string name){

    std::vector<std::string> :: iterator it;
    it = std::find(table_names.begin(), table_names.end(), name);
    
    return it - table_names.begin();
}

void Database::describe_table(std::string name){

    if(!is_table_present(name)){

        Message::FileNotFound(name);
        return;
    }

    Table table = load_table(table_filenames[name_to_filename(name)]);
    table.print_types();

}

void Database::rename_table(std::string name, std::string new_name){

    if(!is_table_present(name)){

        Message::FileNotFound(name);
        return;
    }

    std::string table_filename = table_filenames[name_to_filename(name)];

    //change the name in the table's file
    Table table(table_filename);
    table.set_name(new_name);
    table.save_table(table_filename);

    //change the name in the Database's array of names
    table_filenames[name_to_filename(name)] = new_name;
    
}

void Database::print_table(std::string name){

    Table table = load_table(name);
    Presenter::show_table(table);

}

void Database::add_empty_column(std::string table_name, std::string col_name, Type type){

    Table table = load_table(table_name);
    if(!table.is_loaded_correctly()) return;
    if(Parser::has_whitespace(col_name)){

        Message::Custom("Column name must be a single word.");
        return;
    }

    table.add_empty_column(col_name, type);
    table.save_table(table_filenames[name_to_filename(table_name)]);
    std::cout << "Table saved" << std::endl;
}
void Database::select_rows(std::string name, int col, Record* val){

    Table table = load_table(name);
    if(!table.is_loaded_correctly()) return;

    std::vector<int> row_idx = table.find_rows_by_value(col, val);

    Presenter::print_rows(table.get_rows(), row_idx);
}
void Database::write(){

    std::ofstream database("Database");

    if(database.is_open()){

        for(int i=0; i<table_filenames.size(); i++){


            database << table_filenames[i];
            if(i < table_names[i].size()){

                database << "\n";
            }
        }
    }
}