#include "Utils.h"
#include <unordered_map>
#include <iostream>


RecordNumber* Utils::get_max(RecordNumber* arg, RecordNumber* val_holder){

    if( * arg > *val_holder) return arg;
    return val_holder;
}

RecordNumber* Utils::get_min(RecordNumber* arg, RecordNumber* val_holder){

    if(*arg < *val_holder) return arg;
    return val_holder;
}

RecordNumber* Utils::add(RecordNumber* arg, RecordNumber* val_holder){

    val_holder = *val_holder + *arg;
    return val_holder;
}

RecordNumber* Utils::multiply(RecordNumber* arg, RecordNumber* val_holder){

    val_holder = *val_holder * (*arg);
    return val_holder;
}

RecordNumber* Utils::aggregate(Table table, std::vector<int> idx, int col, std::string operation){

    typedef RecordNumber* (*aggregator_f)(RecordNumber* arg, RecordNumber* val_holder);

    std::unordered_map<std::string, aggregator_f> map_to_aggr = {

        {"min", &Utils::get_min},
        {"max", &Utils::get_max},
        {"sum", &Utils::add},
        {"product", &Utils::multiply}
    };


    RecordNumber* (*aggregator)(RecordNumber* arg, RecordNumber* val_holder) = map_to_aggr[operation];
    std::vector<Row> rows = table.get_rows();

    RecordNumber* val_holder = dynamic_cast<RecordNumber*>(rows[idx[0]].get_records()[col]);

    for(int i=1; i<idx.size(); i++){

        Record* curr_rec = rows[idx[i]].get_records()[col];
        RecordNumber* curr = dynamic_cast<RecordNumber*>(curr_rec);
        val_holder = aggregator(curr, val_holder);
    }


    return val_holder;
}