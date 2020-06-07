#pragma once

#include <vector>
#include "../Record/RecordNumber.h"
#include "../Table/Table.h"

namespace Utils{

    template<typename T>
    std::vector<T> concatenate(std::vector<T> v1, std::vector<T> v2){

        std::vector<T> res;
        
        //walk through first vec
        for(int i=0; i<v1.size(); i++){

            res.push_back(v1[i]);
        }

        //walk thorugh second vec
        for(int i=0; i<v2.size(); i++){

            res.push_back(v2[i]);
        }

        return res;
    }
    
    RecordNumber* add(RecordNumber* arg, RecordNumber* val_holder);
    RecordNumber* multiply(RecordNumber* arg, RecordNumber* val_holder);
    RecordNumber* get_max(RecordNumber* arg, RecordNumber* val_holder);
    RecordNumber* get_min(RecordNumber* arg, RecordNumber* val_holder);

    RecordNumber* aggregate(Table table, std::vector<int> idx, int col, std::string operation);
}
