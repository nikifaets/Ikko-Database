#include "Presenter.h"
#include "../Message/Message.h"
#include <iostream>

void Presenter::show_table(Table table){

    std::vector<Row> rows = table.get_rows();
    if(!rows.size()){

        Message::Custom("Table is empty. Cannot visualize.");
        return;
    }

    for(int i=0; i<rows.size(); i++){

        std::cout << rows[i].to_present_string() << std::endl;
    }
}

void Presenter::print_rows(std::vector<Row> rows, std::vector<int> idx){

    for(int i=0; i<idx.size(); i++){

        std::cout << rows[idx[i]].to_present_string() << std::endl;
    }
}