#include "Table.h"
#include <fstream>
#include "../Message/Message.h"
#include "Parser/Parser.h"
#include <iostream>

void Table::read_table(std::string filename){

    std::ifstream table;
    table.open(filename);

    if(!table.is_open()){

        Message::FileNotFound(filename);
        return;
    }

    std::string line;

    //get type data - first line
    std::getline(table, line);
    row_types = Parser::parse_type_data(line);


    if(!row_types.size()){

        Message::CorruptedTypeInformation(filename);
        return;
    }

    while(std::getline(table, line)){

        Row row(Parser::parse_line(line));

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

    std::ofstream table(filename);

    std::string types = types_to_str();
    table << types << std::endl;

    for(int i=0; i<rows.size(); i++){

        std::string row_string = rows[i].to_string();
        table << row_string;

        if(i < rows.size()-1){

            table << std::endl;
        }
    }
}

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
