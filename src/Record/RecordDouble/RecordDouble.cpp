#include "RecordDouble.h"

void RecordDouble::parse(std::string value){

    this->value = stod(value);
}

double RecordDouble::get_value(){

    return this->value;
}