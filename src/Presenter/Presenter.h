#pragma once

#include "../Table/Table.h"

class Presenter{

    public:

    static void show_table(Table table);
    static void print_rows(std::vector<Row> rows, std::vector<int> idx);
};