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
void Table::read_table(std::string filename){
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

void Table::save_table(std::string filename){

    std::ofstream table(name);

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
std::vector<Row> Table::find_rows_by_value(int column, T* val){


    
    if(column >= col_names.size()){

        Message::WrongNumberOfColumns(column+1, col_names.size());
        return std::vector<Row>();
    }
    
    //check type at current column
    Type type = row_types[column];

    std::cout << "comparison " << std::endl;
    std::cout << val->get_value() << std::endl; // == rows[0].get_records()[column]->get_value();
    //if type == int



}

