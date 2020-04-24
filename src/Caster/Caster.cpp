#include "Caster.h"
#include "../Record/RecordInt/RecordInt.h"
#include "../Record/RecordDouble/RecordDouble.h"
#include "../Table/Parser/Parser.h"
#include <iostream>

Record* Caster::string_to_rec(std::string val){

    Record* rec;

    if(Parser::is_number(val)){

        if(Parser::is_double(val)){

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

