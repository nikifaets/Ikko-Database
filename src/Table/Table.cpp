#include "Table.h"
#include <fstream>
#include "../Message/Message.h"
#include "Parser/Parser.h"
#include <iostream>
#include <type_traits>
#include "../Record/RecordInt/RecordInt.h"
#include "../Record/RecordDouble/RecordDouble.h"

Table::Table(std::string name): name(name){}

Table::Table(){

    name = "";
}
std::string Table::get_name(){

    return name;
}

void Table::set_name(std::string new_name){

    name = new_name;
}

void Table::read_table(std::string location){

    std::string filename = location + "/" + name;

    std::ifstream table;
    table.open(filename);

    if(!table.is_open()){

        Message::FileNotFound(filename);
        return;
    }

    std::string line;
    
    //read column names - first line
    std::getline(table, line);
    col_names = Parser::parse_line_str(line);

    //read type data - second line
    std::getline(table, line);
    row_types = Parser::parse_type_data(line);

    if(!row_types.size()){

        Message::CorruptedTypeInformation(filename);
        return;
    }

    if(row_types.size() != col_names.size()){

        Message::CorruptedTypeInformation(filename);
        return;
    }

    //read rows
    while(std::getline(table, line)){

        Row row(Parser::parse_line(line, row_types));

        if(!validate_row(row)){

            Message::CorruptedRow(rows.size());
            rows.clear();
            return;
        }

        rows.push_back(row);
    }

    table.close();
}

void Table::save_table(std::string location){

    std::string filename = location + "/" + name;

    std::ofstream table(filename);

    std::cout << table.is_open() << " " << name << std::endl;
    //write names
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
    if(records.size() != row_types.size()){

        Message::WrongNumberOfColumns(row_types.size(), records.size());
        return;
    }

    for(int i=0; i<records.size(); i++){

        if(records[i]->get_type() != row_types[i]){
            
            Message::WrongDataType(i);
            return;
        }
    }

    rows.push_back(row);


}
//convert the types of the table to a single string
std::string Table::types_to_str(){

    std::string str;
    for(int i=0; i<row_types.size(); i++){

        Type type = row_types[i];
        str += std::to_string(int(type));
        
        if(i < row_types.size()-1){

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

    
    if(recs.size() != row_types.size()){

        Message::WrongNumberOfColumns(row_types.size(), recs.size());
        return false;
    }

    for(int i=0; i<recs.size(); i++){

        if(recs[i]->get_type() != row_types[i]){

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

    for(int i=0; i<row_types.size(); i++){

        int type = int(row_types[i]);
        types_str += types[type];

        if(i<row_types.size()-1){

            types_str += " ";
        }
    }    
    std::cout << types_str << std::endl;
}

///template <typename T, typename std::enable_if<std::is_base_of<Record, T>::value>::type* = nullptr>
std::vector<int> Table::find_rows_by_value(int column, Record* val){


    std::vector<int> found_rows;

    if(column >= col_names.size()){

        Message::WrongNumberOfColumns(column, col_names.size());
        return found_rows;
    }
    
    //check type at current column
    Type type = row_types[column];
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

