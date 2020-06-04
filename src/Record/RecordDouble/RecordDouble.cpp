#include "RecordDouble.h"
#include <math.h>

RecordDouble::RecordDouble(){}

RecordDouble::RecordDouble(double val) : value(val) {}
RecordDouble::RecordDouble(std::string val){

    parse(val);
}

void RecordDouble::parse(std::string value){

    this->value = stod(value);
}

double RecordDouble::get_value() const{

    return this->value;
}

std::string RecordDouble::to_string(){

    if(empty){

        return NULL_REC;
    }
    return std::to_string(value);
}

Type RecordDouble::get_type() const{

    return Double;
}

bool RecordDouble::operator == (const Record& other) const{

    if(const RecordDouble* r_double = dynamic_cast<const RecordDouble*>(&other)){

        return abs(r_double->get_value() - value) <= COMP_EPS;
    }

    return false;
}