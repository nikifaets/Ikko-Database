#include "Caster.h"
#include "../Record/RecordInt/RecordInt.h"
#include "../Record/RecordDouble/RecordDouble.h"
#include <iostream>

Record* Caster::string_to_rec(std::string val){

    Record* rec;

    if(is_number(val)){

        if(is_double(val)){

            rec = new RecordDouble(val);

        }

        else{

            rec = new RecordInt(val);
        }
    }

    return rec;
}

Record* Caster::type_to_rec(Type type){

    Record* rec;

    if(type == Int){

        return new RecordInt();
    }

    if(type == Double){

        return new RecordDouble();
    }
}

bool Caster::is_number(std::string val){

    return val[0] >= '0' && val[0] <= '9';

}

bool Caster::is_double(std::string val){

    return val.find(".") != std::string::npos;
}