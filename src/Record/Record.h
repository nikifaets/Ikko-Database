#pragma once
#include <string>

enum Type{Int, Double, String, Null};

class Record{

    bool empty = true;

    public:

    virtual void parse(std::string value) = 0;
    bool is_empty();
    

};