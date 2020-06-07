#include "RecordDouble.h"
#include <math.h>
#include <iostream>

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

std::string RecordDouble::to_string() const{

    if(empty){

        return NULL_REC;
    }
    return std::to_string(value);
}

std::string RecordDouble::to_present_string () const{

    return to_string();
}
Type RecordDouble::get_type() const{

    return Double;
}

bool RecordDouble::operator == (const Record& other) const{

    if(const RecordDouble* r_double = dynamic_cast<const RecordDouble*>(&other)){

        return abs(r_double->get_value() - value) <= COMP_EPS || (r_double->is_empty() && empty);
    }

    return false;
}

RecordNumber* RecordDouble::operator + (const RecordNumber& other){

    if(const RecordDouble* r_double = dynamic_cast< const RecordDouble*>(&other)){

        if(empty || r_double->is_empty()) return this;
        return new RecordDouble(r_double->get_value() + value);
    }

    return new RecordDouble(0);
}

RecordNumber* RecordDouble:: operator *(const RecordNumber& other){

    if(const RecordDouble* r_double = dynamic_cast< const RecordDouble*>(&other)){

        if(empty || r_double->is_empty()) return this;
        return new RecordDouble(r_double->get_value() * value);
    }

    return  new RecordDouble(0);
}

bool RecordDouble::operator > (const RecordNumber& other) const{

    if(const RecordDouble* r_double = dynamic_cast< const RecordDouble*>(&other)){

        return r_double->get_value() < value || (r_double->is_empty() && this->empty);
    }

    return false;

}
bool RecordDouble:: operator < (const RecordNumber& other) const{

    if(const RecordDouble* r_double = dynamic_cast< const RecordDouble*>(&other)){

        return r_double->get_value() > value || (r_double->is_empty() && this->empty);
    }

    return false;
}