#pragma once

#include "Row/Row.h"

class Table{

    std::vector <Row> rows;

    public:

    void read_table(std::string filename);

};