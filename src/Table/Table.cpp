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

    old_filename = filename;

    std::string line;
    while(std::getline(table, line)){

        Row row(Parser::parse_line(line));
        rows.push_back(row);
    }

    table.close();
}

void Table::save_table(std::string filename){

    std::ofstream table(filename);

    for(int i=0; i<rows.size(); i++){

        std::string row_string = rows[i].to_string();
        table << row_string;

        if(i < rows.size()-1){

            table << std::endl;
        }
    }
}

std::vector<Row> Table::get_rows(){

    return rows;
}
