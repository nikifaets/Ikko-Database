#include "RecordString.h"
#include "iostream"
#include <sstream>

RecordString::RecordString(std::string val) : value_raw(val){

    parse(val);
}
RecordString::RecordString(){}

std::string RecordString::get_value() const{

    return value;
}

void RecordString::parse(std::string val_raw){

    std::stringstream ss(val_raw);
    std::string val;
    ss >> val;
/*
    if(val[0] == '\"'){
         
         val.erase(val.begin());
         val.erase(val.begin()+val.size()-1);
    }

    for(int i=0; i<val.size(); i++){

        if(val[i] == '\\' && (val[i+1] == '\\' || val[i+1] == '\"')){
            val.erase(val.begin()+i);
            i--;
        }

    }
*/
    value = val;

}

std::string RecordString::to_string(){

    if(empty){

        return NULL_REC;
    }
    return value_raw;
}

std::string RecordString::to_present_string(){

    if(empty){

        return NULL_REC;
    }

    return value;
}

Type RecordString::get_type() const{

    return String;
}

bool RecordString::operator == (const Record& other) const{

    if(const RecordString* r_str = dynamic_cast<const RecordString*>(&other)){

        return !(value.compare(r_str->get_value()) || (empty && r_str->is_empty()));
    }
}