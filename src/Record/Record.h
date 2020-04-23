#pragma once
#include <string>

class Record{

    const std::string type_name;

    public:

    virtual void parse(std::string value) = 0;

};