#include "Row.h"
#include "../../Caster/Caster.h"
#include "../../Record/RecordInt/RecordInt.h"
#include <iostream>

Row::Row(){}
Row::Row(std::vector<Record*> recs){

    records = recs;

}
void Row::add_empty_record(Type type){

    Record* new_rec = Caster::type_to_rec(type);
    new_rec->set_empty(true);
    records.push_back(new_rec); 
}

void Row::add_record(Record* rec){

    records.push_back(rec);
}

void Row::add_record(std::string val){

    Record* new_rec = Caster::string_to_rec(val);
    records.push_back(new_rec);
}

std::string Row::to_string(){

    std::string row_string;
    for(int i=0; i<records.size(); i++){

        std::string rec_string = records[i]->to_string();
        row_string += rec_string;

        if(i < records.size()-1){

            row_string += '\t';
        }      

    }

    return row_string;
}

std::string Row::to_present_string(){

    std::string row_string;
    for(int i=0; i<records.size(); i++){

        std::string rec_string = records[i]->to_present_string();
        row_string += rec_string;

        if(i<records.size()-1){

            row_string += '\t';
        }
    }

    return row_string;
}

std::vector <Record*> Row::get_records(){

    return this->records;
}

void Row::change_rec(int col_idx, Record* rec){

    records[col_idx] = rec;
}