#include "Parser.h"
#include "../../Caster/Caster.h"
#include <algorithm>
#include <iostream>
#include "../../Message/Message.h"


const std::unordered_set<char> Parser::separators = {'\t', ' '};

bool Parser::is_number(std::string val){

    for(int i=0; i<val.size(); i++){

        if(!is_digit(val[i]) && val[i] != '.'){

            return false;
        }
    }

    
    return std::count(val.begin(), val.end(), '.') < 2;

}

bool Parser::is_int(std::string val){

    return is_number(val) && std::count(val.begin(), val.end(), '.') == 0;
}

bool Parser::is_double(std::string val){

    return val.find(".") != std::string::npos;
}

bool Parser::is_digit(char c){

    return c >= '0' && c <= '9';
}

bool Parser::is_separator(char c){

    return separators.find(c) != separators.end();
}

std::vector<Record*> Parser::parse_line(std::string line, std::vector<Type> types){

    std::vector<Record*> recs;

    std::vector<std::string> line_str = parse_line_str(line);

    for(int i=0; i<line_str.size(); i++){

        Record* rec;

        if(!line_str[i].compare(NULL_REC)){

            rec = Caster::type_to_rec(types[i]);            
            rec->set_empty(true);

        }

        else{

            rec = Caster::string_to_rec(line_str[i]);

        }

        if(rec->get_type() == Invalid){
            
            Message::InvalidRecord(i);
            return std::vector<Record*>();

        }

        recs.push_back(rec);
    }

    return recs;
}

std::vector<std::string> Parser::parse_line_str(std::string line){

    std::vector<std::string> line_recs;

    for(int i=0; i<line.size(); i++){

        if(is_separator(line[i])) continue;


        std::string val = read_until_whitespace(line.substr(i));
        i += val.size();

        line_recs.push_back(val);

    }

    return line_recs;
}

std::vector<Type> Parser::parse_type_data(std::string line){

    std::vector<std::string> line_recs = parse_line_str(line);
    bool valid = validate_type_data(line_recs);

    if(!valid){

        return std::vector<Type>();

    }
    std::vector<Type> types;

    for(int i=0; i<line_recs.size(); i++){

        int rec_type = stoi(line_recs[i]);
        Type type = static_cast<Type>(rec_type);

        if(type > Null){

            //return empty vector
            return std::vector<Type>();
        }

        types.push_back(type);
    }

    return types;
}

bool Parser::validate_type_data(std::vector<std::string> line_recs){

    for(int i=0; i<line_recs.size(); i++){

        if(!is_int(line_recs[i])){

            return false;
        }
    }

    return true;
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