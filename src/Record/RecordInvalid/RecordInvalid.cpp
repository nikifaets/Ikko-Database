#include "RecordInvalid.h"

Type RecordInvalid::get_type(){

    return type;
}

void RecordInvalid::parse(std::string value){}
std::string RecordInvalid::to_string(){}

bool RecordInvalid::operator == (const Record& other) const{

    if(const RecordInvalid* r_invalid = dynamic_cast<const RecordInvalid*>(&other)){

        return true;
    }

    return false;
}