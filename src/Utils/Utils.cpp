#pragma once
#include "Utils.h"
#include <vector>

template<typename T>
std::vector<T> Utils::concatenate(std::vector<T> v1, std::vector<T> v2){

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