#include "RecordDouble.h"


RecordDouble::RecordDouble(){}
RecordDouble::RecordDouble(std::string val){

    parse(val);
}

void RecordDouble::parse(std::string value){

    this->value = stod(value);
}

double RecordDouble::get_value(){

    return this->value;
}

std::string RecordDouble::to_string(){

    return std::to_string(value);
}