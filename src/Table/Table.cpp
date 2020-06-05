#include "Table.h"
#include <fstream>
#include "../Message/Message.h"
#include "Parser/Parser.h"
#include <iostream>
#include <type_traits>
#include "../Record/RecordInt/RecordInt.h"
#include "../Record/RecordDouble/RecordDouble.h"
#include "../Caster/Caster.h"

Table::Table(std::string filename){

    read_table(filename);
}

Table::Table(){}

std::string Table::get_name(){

    return name;
}

void Table::set_name(std::string new_name){

    name = new_name;
}

void Table::read_table(std::string filename){

    std::ifstream table;
    table.open(filename);

    if(!table.is_open()){

        Message::FileNotFound(filename);
        loaded = false;
        return;
    }

    std::string line;
    
    //read table name - first line
    std::getline(table, line);
    name = line;

    //read column names - second line
    std::getline(table, line);
    col_names = Parser::parse_line_str(line);

    //read type data - third line
    std::getline(table, line);
    col_types = Parser::parse_type_data(line);

    if(!col_types.size()){

        Message::CorruptedTypeInformation(filename);
        loaded = false;
        return;
    }

    if(col_types.size() != col_names.size()){

        Message::CorruptedTypeInformation(filename);
        loaded = false;
        return;
    }

    //read rows
    while(std::getline(table, line)){

        Row row(Parser::parse_line(line, col_types));

        if(!validate_row(row)){

            Message::CorruptedRow(rows.size());
            rows.clear();
            loaded = false;
            return;
        }

        rows.push_back(row);
    }

    table.close();
}

bool Table::is_loaded_correctly(){

    return loaded;
}

void Table::save_table(std::string filename){

    std::ofstream table(filename);

    if(!table.is_open()){

        Message::CannotWriteFile(filename);
        return;
    }
    //write table name
    table << name << std::endl;

    //write column names
    std::string names = col_names_to_str();
    table << names << std::endl;

    //write types
    std::string types = types_to_str();
    table << types << std::endl;

    //write rows
    for(int i=0; i<rows.size(); i++){

        std::string row_string = rows[i].to_string();
        table << row_string;

        if(i < rows.size()-1){

            table << std::endl;
        }
    }

    table.close();
}

void Table::add_row(Row row){

    std::vector<Record*> records = row.get_records();
    
    //validate row types
    if(records.size() != col_types.size()){

        Message::WrongNumberOfColumns(col_types.size(), records.size());
        return;
    }

    for(int i=0; i<records.size(); i++){

        if(records[i]->get_type() != col_types[i]){
            
            Message::WrongDataType(i);
            return;
        }
    }

    rows.push_back(row);


}

void Table::delete_rows(int col_idx, Record* val){

    
    std::vector<int> indices = find_rows_by_value(col_idx, val);
    if(! indices.size()) return;

    for(int i=0; i<indices.size(); i++){

        // subtract i because with each erasion, the elements after indices[i] shift one to the left
        rows.erase(rows.begin() + indices[i] - i); 
    }
}

void Table::add_empty_column(std::string name, Type type){

    col_names.push_back(name);
    col_types.push_back(type);


    for(int i=0; i<rows.size(); i++){

        rows[i].add_empty_record(type);
    }

    
}
//convert the types of the table to a single string
std::string Table::types_to_str(){

    std::string str;
    for(int i=0; i<col_types.size(); i++){

        Type type = col_types[i];
        str += std::to_string(int(type));
        
        if(i < col_types.size()-1){

            str += '\t';
        }
    }

    return str;
}

//convert the names of the table columns to a single string
std::string Table::col_names_to_str(){

    std::string str;

    for(int i=0; i<col_names.size(); i++){

        str += col_names[i];

        if(i < col_names.size()-1){

            str += '\t';
        }

    }

    return str;
}

bool Table::validate_row(Row row){

    std::vector<Record*> recs = row.get_records();

    if(recs.size() == 0){

        return false;
    }

    
    if(recs.size() != col_types.size()){

        Message::WrongNumberOfColumns(col_types.size(), recs.size());
        return false;
    }

    for(int i=0; i<recs.size(); i++){

        if(recs[i]->get_type() != col_types[i]){

            Message::WrongDataType(i);
            return false;
        }
    }

    return true;
}

std::vector<Row> Table::get_rows(){

    return rows;
}

void Table::print_types(){

    std::string types[3] = {"Int", "Double", "String"};
    std::string types_str;

    for(int i=0; i<col_types.size(); i++){

        int type = int(col_types[i]);
        types_str += types[type];

        if(i<col_types.size()-1){

            types_str += " ";
        }
    }    
    std::cout << types_str << std::endl;
}

void Table::count(int col_idx, Record* val){

    std::vector<int> indices = find_rows_by_value(col_idx, val);
    if(!indices.size()) return;

    Message::Custom("Amount of rows that contain the value " + (val->to_string()) + ": " + std::to_string(indices.size()));
}
///template <typename T, typename std::enable_if<std::is_base_of<Record, T>::value>::type* = nullptr>
std::vector<int> Table::find_rows_by_value(int column, Record* val){


    std::vector<int> found_rows;

    if(column >= col_names.size()){

        Message::WrongNumberOfColumns(column, col_names.size());
        return found_rows;
    }
    
    //check type at current column
    Type type = col_types[column];
    if(val->get_type() != type){

        return found_rows;
    }

    //search all rows for the value

    for(int i=0; i<rows.size(); i++){

        Record* curr = rows[i].get_records()[column];

        if(*curr == *val){

            found_rows.push_back(i);
        }
    }

    return found_rows;

}

void Table::update_column(int search_col, Record* search_val, int target_col, Record* target_val){

    if(search_col >= col_types.size() || search_col >= col_types.size()){

        Message::WrongNumberOfColumns(col_types.size(), std::max(search_col, target_col));
        return;
    }

    if(search_val->get_type() != col_types[search_col] || target_val->get_type() != col_types[target_col]){

        Message::Custom("Record types do not match the column types.");
        return;
    }

    std::vector<int> indices = find_rows_by_value(search_col, search_val);

    for(int i=0; i<indices.size(); i++){

        rows[indices[i]].change_rec(target_col, target_val);
    }
}

