#include "Row.h"
#include "../../Caster/Caster.h"
#include "../../Record/RecordInt/RecordInt.h"
#include <iostream>

void Row::add_empty_record(Type type){

    Caster caster;
    Record* new_rec = caster.type_to_rec(type);
    records.push_back(new_rec); 
}

void Row::add_record(Record* rec){

    records.push_back(rec);
}

void Row::add_record(std::string val){

    Caster caster;
    Record* new_rec = caster.string_to_rec(val);
    records.push_back(new_rec);
}

std::vector <Record*> Row::get_records(){

    return this->records;
}