#include "Record.h"

bool Record::is_empty() const {

    return this->empty;
}

void Record::set_empty(bool empty){

    this->empty = empty;
}

Type Record::get_type() const{

    return this->type;
}

