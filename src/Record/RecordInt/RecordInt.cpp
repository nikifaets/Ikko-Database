#include "RecordInt.h"
#include <string>

RecordInt::RecordInt() {}

RecordInt::RecordInt(std::string val){

    parse(val);

}

void RecordInt::parse(std::string value){

    int multiplier = 1;

    if(value[0] == '-' || value[0] == '+'){

        if (value[0] == '-'){}
    }
    this->value = stoi(value);
}

long long RecordInt::get_value(){

    return this->value;
}

std::string RecordInt::to_string(){

    if(empty){
        
        return NULL_REC;
    }

    return std::to_string(value);
}

Type RecordInt::get_type(){

    return type;
}