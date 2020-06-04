#include "Caster.h"
#include "../Record/RecordInt/RecordInt.h"
#include "../Record/RecordDouble/RecordDouble.h"
#include "../Record/RecordInvalid/RecordInvalid.h"
#include "../Table/Parser/Parser.h"
#include <iostream>

Record* Caster::string_to_rec(std::string val){

    Record* rec = new RecordInvalid();

    if(Parser::is_number(val)){

        if(Parser::is_double(val)){

            return new RecordDouble(val);

        }

        else{

            return new RecordInt(val);
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

