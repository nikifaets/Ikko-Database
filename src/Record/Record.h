#pragma once
#include <string>

enum Type{Int, Double, String, Null};

class Record{

    bool empty = false;

    public:

    virtual void parse(std::string value) = 0;
    bool is_empty();
    void set_empty(bool empty);
    virtual std::string to_string() = 0;
    

};