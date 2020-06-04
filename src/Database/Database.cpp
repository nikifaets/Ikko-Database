#include "Database.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "../Message/Message.h"

const std::string Database::DATABASE_LOCATION = "../src/Database/Database";
const std::string Database::TABLES_LOCATION = "../src/Database/Tables";

Database::Database(){

    std::ifstream database(DATABASE_LOCATION);

    //parse lines
    std::string line;

    while(std::getline(database, line)){

        table_names.push_back(line);
    }

}

Table Database::load_table(std::string name){

    std::vector<std::string>::iterator it = std::find(table_names.begin(), table_names.end(), name);

    if(it == table_names.end()){

        Message::FileNotFound(name);
        return Table();


    } 

    Table table(name);
    table.read_table(TABLES_LOCATION);

    return table;
}

void Database::show_tables(){

    std::cout << "Tables in database:" << std::endl;

    for(int i=0; i<table_names.size(); i++){

        std::cout << table_names[i] << std::endl;
    }
}

void Database::import_table(std::string filename){

    if(is_table_present(filename)){

        Message::NameTaken();
        return;
    }    

    std::ofstream database("Database", std::ios::app);
    database << filename;
}

void Database::export_table(std::string name, std::string filename){

    if(!is_table_present(name)){

        Message::FileNotFound(name);
        return;
    }

    Table table = load_table(name);
    table.save_table(filename);
}

bool Database::is_table_present(std::string name){

    Table table = load_table(name);
    if(!table.get_name().compare("")){

        Message::NameTaken();
        return false;
    }

    return true;
}

void Database::describe_table(std::string name){

    if(!is_table_present(name)){

        Message::FileNotFound(name);
        return;
    }

    Table table = load_table(name);
    table.print_types();

}

void Database::rename_table(std::string name, std::string new_name){

    if(!is_table_present(name)){

        Message::FileNotFound(name);
        return;
    }

    Table table = load_table(name);
    table.set_name(new_name);

    std::vector<std::string>::iterator it = std::find(table_names.begin(), table_names.end(), name);
    *it = new_name;
    refresh();
    
}

void Database::refresh(){

    std::ofstream database("Database");

    if(database.is_open()){

        for(int i=0; i<table_names.size(); i++){


        database << table_names[i];
        if(i < table_names[i].size()){

            database << "\n";
        }
        }
    }
}