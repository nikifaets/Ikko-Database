#include "RecordInt.h"
#include <string>
#include <iostream>

RecordInt::RecordInt() {}

RecordInt::RecordInt(std::string val){

    parse(val);

}

RecordInt::RecordInt(int val) : value(val){}

void RecordInt::parse(std::string value){

    int multiplier = 1;

    if(value[0] == '-' || value[0] == '+'){

        if (value[0] == '-'){}
    }
    this->value = stoi(value);
}

long long RecordInt::get_value() const{

    return this->value;
}

std::string RecordInt::to_string() const{

    if(empty){
        
        return NULL_REC;
    }

    return std::to_string(value);
}

std::string RecordInt::to_present_string() const{

    return to_string();
}

Type RecordInt::get_type() const{

    return Int;
}

bool RecordInt::operator ==(const Record& other) const{

    if(const RecordInt* r_int = dynamic_cast< const RecordInt*>(&other)){

        return r_int->get_value() == value || (r_int->is_empty() && this->empty);
    }

    return false;
}

RecordNumber* RecordInt::operator + (const RecordNumber& other){

    if(const RecordInt* r_int = dynamic_cast< const RecordInt*>(&other)){

        if(empty || r_int->is_empty()) return this;
        return new RecordInt(r_int->get_value() + value);
    }

    return new RecordInt(0);
}

RecordNumber* RecordInt:: operator *(const RecordNumber& other){

    if(const RecordInt* r_int = dynamic_cast< const RecordInt*>(&other)){

        if(empty || r_int->is_empty()) return this;
        return new RecordInt(r_int->get_value() * value);
    }

    return  new RecordInt(0);
}

bool RecordInt::operator > (const RecordNumber& other) const{

    if(const RecordInt* r_int = dynamic_cast< const RecordInt*>(&other)){

        return r_int->get_value() < value || (r_int->is_empty() && this->empty);
    }

    return false;

}
bool RecordInt:: operator < (const RecordNumber& other) const{

    if(const RecordInt* r_int = dynamic_cast< const RecordInt*>(&other)){

        return r_int->get_value() > value || (r_int->is_empty() && this->empty);
    }

    return false;
}


