#include "Parser.h"
#include "../../Caster/Caster.h"

bool Parser::is_number(std::string val){

    return val[0] >= '0' && val[0] <= '9';

}

bool Parser::is_double(std::string val){

    return val.find(".") != std::string::npos;
}

bool Parser::is_digit(char c){

    return c >= '0' && c <= '9';
}

std::vector<Record*> Parser::parse_line(std::string line){

    std::vector<Record*> recs;

    for(int i=0; i<line.size(); i++){

        if(line[i] < MIN_ASCII) continue;

        if(is_digit(line[i])){

            std::string val = read_until_whitespace(line.substr(i));
            i += val.size();

            Record* rec = Caster::string_to_rec(val);
            recs.push_back(rec);
        }
    }

    return recs;
}

std::string Parser::read_until_whitespace(std::string str){

    std::string parsed;
    int it = 0;
    while(str[it] >= MIN_ASCII){

        parsed.push_back(str[it]);
        it++;
    }

    return parsed;

}