#include "Presenter.h"
#include <iostream>

void Presenter::show_table(Table table){

    std::vector<Row> rows = table.get_rows();

    for(int i=0; i<rows.size(); i++){

        std::cout << rows[i].to_string() << std::endl;
    }
}

void Presenter::print_rows(std::vector<Row> rows, std::vector<int> idx){

    for(int i=0; i<idx.size(); i++){

        std::cout << rows[idx[i]].to_string() << std::endl;
    }
}