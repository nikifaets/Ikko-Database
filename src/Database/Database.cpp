#include "Database.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "../Message/Message.h"
#include "../Presenter/Presenter.h"
#include "../Table/Parser/Parser.h"
#include "../Utils/Utils.h"

const std::string Database::DATABASE_LOCATION = "../src/Database/Database";
const std::string Database::TABLES_LOCATION = "../src/Database/Tables";

Database::Database(){

    std::ifstream database(DATABASE_LOCATION);

    //parse all tables' files
    std::string filename;

    while(std::getline(database, filename)){

        Table table(filename);
        std::string name = table.get_name();

        if(!table.is_loaded_correctly()) continue;
        if(is_table_present(name)) continue;

        table_filenames.push_back(filename);
        table_names.push_back(name);
    }


}

Table Database::load_table(std::string name){

    if(!is_table_present(name)){

        Message::TableNotFound(name);
        return Table();
    }


    Table table(name_to_filename(name));
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

    table_names.push_back(name);
    table_filenames.push_back(filename);

}

void Database::export_table(std::string name, std::string filename){

    if(!is_table_present(name)){

        Message::TableNotFound(name);
        return;
    }


    Table table(name_to_filename(name));
    table.save_table(filename);
}

bool Database::is_table_present(std::string name){

    std::vector<std::string>::iterator it;
    it = std::find(table_names.begin(), table_names.end(), name);

    return it != table_names.end();
}

std::string Database::name_to_filename(std::string name){

    std::vector<std::string> :: iterator it;
    it = std::find(table_names.begin(), table_names.end(), name);
    
    int idx = it - table_names.begin();

    return table_filenames[idx];
}

void Database::describe_table(std::string name){

    if(!is_table_present(name)){

        Message::TableNotFound(name);
        return;
    }

    Table table = load_table(name);
    table.print_types();

}

void Database::rename_table(std::string name, std::string new_name){

    if(!is_table_present(name)){

        Message::TableNotFound(name);
        return;
    }

    std::string table_filename = name_to_filename(name);

    //change the name in the table's file
    Table table(table_filename);
    table.set_name(new_name);
    table.save_table(table_filename);

    //change the name in the Database's array of names
    std::vector<std::string> :: iterator it = std::find(table_names.begin(), table_names.end(), name);
    int name_idx = it - table_names.begin();
    table_names[name_idx] = new_name;
    
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
    table.save_table(name_to_filename(table_name));
}


void Database::insert(std::string table_name, Row row){

    Table table = load_table(table_name);
    table.add_row(row);
    table.save_table(name_to_filename(table_name));
}

void Database::delete_rows(std::string table_name, int col_idx, Record* val){

    Table table = load_table(table_name);
    table.delete_rows(col_idx, val);
    table.save_table(name_to_filename(table_name));
}
void Database::select_rows(std::string name, int col, Record* val){

    Table table = load_table(name);
    if(!table.is_loaded_correctly()) return;

    std::vector<int> row_idx = table.find_rows_by_value(col, val);

    Presenter::print_rows(table.get_rows(), row_idx);
}

void Database::update_column(std::string table_name, int search_col, Record* search_val, int target_col, Record* target_val){

    Table table = load_table(table_name);
    table.update_column(search_col, search_val, target_col, target_val);
    table.save_table(name_to_filename(table_name));

}

void Database::count_cols(std::string table_name, int col_idx, Record* val){

    Table table = load_table(table_name);
    table.count(col_idx, val);
}

void Database::innerjoin(std::string table1_name, int col1, std::string table2_name, int col2){

    if(! is_table_present(table1_name)){

        Message::TableNotFound(table1_name);
        return;
    }

    if(! is_table_present(table2_name)){

        Message::TableNotFound(table2_name);
        return;
    }

    Table table1 = load_table(table1_name);
    Table table2 = load_table(table2_name);

    if(! table1.is_loaded_correctly() || ! table2.is_loaded_correctly()) return;

    //compare types
    std::vector<Type> types1 = table1.get_types();
    std::vector<Type> types2 = table2.get_types();

    if(types1[col1] != types2[col2]){

        Message::Custom("Data types are not the same. Cannot perform innerjoin.");
        return;
    }

    //everything is validated, start innerjoin
    std::string new_table_name = "InnerJoin_" + table1.get_name() + "_" + table2.get_name();

    //create new names for the table columns
    std::vector<std::string> new_col_names;

    //from the first table
    std::vector<std::string> col_names1 = table1.get_col_names();

    for(int i=0; i<col_names1.size(); i++){

        new_col_names.push_back(table1.get_name() + "_" + col_names1[i]);
    }

    //from the second table
    std::vector<std::string> col_names2 = table2.get_col_names();

    for(int i=0; i<col_names2.size(); i++){
        
        new_col_names.push_back(table2.get_name() + "_" + col_names2[i]);
    }

    std::vector<Type> new_types = Utils::concatenate(table1.get_types(), table2.get_types());


    Table table(new_table_name, new_col_names, new_types);
    //start searching for same values
    std::vector<Row> rows1 = table1.get_rows();
    std::vector<Row> rows2 = table2.get_rows();

    for(int i=0; i<rows1.size(); i++){

        Record* search_val = rows1[i].get_records()[col1];
        std::vector<int> rows_found = table2.find_rows_by_value(col2, search_val);
        for(int j=0; j<rows_found.size(); j++){

            Row new_row = Utils::concatenate(rows1[i].get_records(), rows2[rows_found[j]].get_records());
            table.add_row(new_row);
            
        }
    }

    std::string table_save_location = TABLES_LOCATION + "/_" + new_table_name;
    table.save_table(table_save_location);
    import_table(table_save_location);
    
    Message::Custom("Innerjoin was succesful. This is the new table: ");
    Presenter::show_table(table);
    
}

void Database::aggregate(std::string table_name, int search_col, Record* search_val, int target_col, std::string operation){

    Table table = load_table(table_name);
    if(!table.is_loaded_correctly()){

        Message::TableNotFound(table_name);
        return;
    }

    std::vector<Type> table_types = table.get_types();

    if(search_col > table_types.size() || target_col > table_types.size()){

        Message::WrongNumberOfColumns(table_types.size()-1, std::max(search_col, target_col));
        return;
    }

    std::unordered_set<std::string> operations {"min", "max", "sum", "product"};
    if(operations.find(operation) == operations.end()){

        Message::InvalidInput();
        return;
    }

    if(table_types[search_col] > Type::Double || table_types[target_col] > Type::Double ||
        search_val->get_type() > Type::Double){

        Message::Custom("Data types should be numeric.");
        return;
    }

    std::vector<int> idx = table.find_rows_by_value(search_col, search_val);

    Record* res = Utils::aggregate(table, idx, target_col, operation);
    std::cout << "Result of aggregation: " << std::endl;
    std::cout << res->to_present_string() << std::endl;

}
void Database::write(std::string path){

    std::ofstream database(path);

    if(database.is_open()){

        for(int i=0; i<table_filenames.size(); i++){


            database << table_filenames[i];
            if(i < table_names[i].size()){

                database << "\n";
            }
        }
    }
}