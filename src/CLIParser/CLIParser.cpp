#include "CLIParser.h"
#include "../Table/Parser/Parser.h"
#include "../Message/Message.h"
#include "../Caster/Caster.h"
#include "../Record/RecordInvalid/RecordInvalid.h"
#include <iostream>
#include <sstream>

Database CLIParser::database;
bool CLIParser::exit_flag = false;
const std::unordered_set<std::string> CLIParser::commands = {
        "save", "saveas", "exit", "help", "showtables", "import", "describe",
        "print", "export", "select", "addcolumn", "update", "delete",
        "insert", "innerjoin", "rename", "count", "aggregate"
        };

std::unordered_map<std::string, std::function<void(std::string, std::vector<std::string>)> > CLIParser::map_to_parser;
std::unordered_map<std::string, std::function<void(std::string, std::vector<std::string>)> > CLIParser::map_to_parser_sir;
std::unordered_map<std::string, std::function<void(std::string, std::vector<std::string>)> > CLIParser::map_to_parser_ss;

std::unordered_map<std::string, std::function<void()> > CLIParser::command_to_func_noargs;
std::unordered_map<std::string, std::function<void(std::string)> > CLIParser::command_to_func_s;
std::unordered_map<std::string, std::function<void(std::string, std::string)> > CLIParser::command_to_func_ss;
std::unordered_map<std::string, std::function<void(std::string, int, Record*)> > CLIParser::command_to_func_sir;
std::unordered_map<std::string, std::function<void(std::string, std::string, Type)> > CLIParser::command_to_func_sst;
std::unordered_map<std::string, std::function<void(std::string, int, Record*, int, Record*)> > CLIParser::command_to_func_sirir;
std::unordered_map<std::string, std::function<void(std::string, std::vector<Record*>)> > CLIParser::command_to_func_sv;
std::unordered_map<std::string, std::function<void(std::string, int, std::string, int)> > CLIParser::command_to_func_sisi;
std::unordered_map<std::string, std::function<void(std::string, int, Record*, int, std::string)> > CLIParser::command_to_func_siris;


CLIParser::CLIParser(){

    fill_maps();
}

void CLIParser::instantiate(){

    Database dummy_database;
    database = dummy_database;

    fill_maps();

}
void CLIParser::parse(){

    while(!exit_flag){

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> parsed_line = Parser::parse_line_str(input);
        if(parsed_line.size() < 1){
            continue;
        }

        std::string action = parsed_line[0];
        parsed_line.erase(parsed_line.begin());

        if(commands.find(action) == commands.end()){

            Message::Custom("Command not found.");
            continue;
        }

        map_to_parser[action](action, parsed_line);

    }
}
void CLIParser::fill_maps(){

    //noargs parse mapper
    CLIParser::map_to_parser["showtables"] = CLIParser::parse_noargs;
    CLIParser::map_to_parser["save"] = CLIParser::parse_noargs;
    CLIParser::map_to_parser["help"] = CLIParser::parse_noargs;
    CLIParser::map_to_parser["exit"] = CLIParser::parse_noargs;

    //s parse mapper
    CLIParser::map_to_parser["import"] = CLIParser::parse_s;
    CLIParser::map_to_parser["describe"] = CLIParser::parse_s;
    CLIParser::map_to_parser["print"] = CLIParser::parse_s;
    CLIParser::map_to_parser["saveas"] = CLIParser::parse_s;

    //ss parse mapper
    CLIParser::map_to_parser["export"] = CLIParser::parse_ss;
    CLIParser::map_to_parser["rename"] = CLIParser::parse_ss;

    //sir parse mapper
    CLIParser::map_to_parser["select"] = CLIParser::parse_sir;
    CLIParser::map_to_parser["delete"] = CLIParser::parse_sir;
    CLIParser::map_to_parser["count"] = CLIParser::parse_sir;

    //sst parse mapper
    CLIParser::map_to_parser["addcolumn"] = CLIParser::parse_sst;

    //sisi parse mapper
    CLIParser::map_to_parser["innerjoin"] = CLIParser::parse_sisi;

    //sirir parse mapper
    CLIParser::map_to_parser["update"] = CLIParser::parse_sirir;

    //sv parse mapper
    CLIParser::map_to_parser["insert"] = CLIParser::parse_sv;

    //siris parse mapper
    CLIParser::map_to_parser["aggregate"] = CLIParser::parse_siris;

    //noargs action mapper
    CLIParser::command_to_func_noargs["showtables"] = CLIParser::send_show;
    CLIParser::command_to_func_noargs["save"] = CLIParser::save;
    CLIParser::command_to_func_noargs["help"] = CLIParser::help;
    CLIParser::command_to_func_noargs["exit"] = CLIParser::exit;

    //s action mapper
    CLIParser::command_to_func_s["import"] = CLIParser::send_import;
    CLIParser::command_to_func_s["describe"] = CLIParser::send_describe;
    CLIParser::command_to_func_s["print"] = CLIParser::send_print;
    CLIParser::command_to_func_s["saveas"] = CLIParser::save_as;

    //ss action mapper
    CLIParser::command_to_func_ss["rename"] = CLIParser::send_rename;
    CLIParser::command_to_func_ss["export"] = CLIParser::send_export;

    //sir action mapper
    CLIParser::command_to_func_sir["select"] = CLIParser::send_select;
    CLIParser::command_to_func_sir["delete"] = CLIParser::send_delete;
    CLIParser::command_to_func_sir["count"] = CLIParser::send_count;

    //sst action mapper
    CLIParser::command_to_func_sst["addcolumn"] = CLIParser::send_add_column;

    //sisi action mapper
    CLIParser::command_to_func_sisi["innerjoin"] = CLIParser::send_innerjoin;

    //sirir action mapper
    CLIParser::command_to_func_sirir["update"] = CLIParser::send_update;

    //sv action mapper
    CLIParser::command_to_func_sv["insert"] = CLIParser::send_insert;

    //siris action mapper
    CLIParser::command_to_func_siris["aggregate"] = CLIParser::send_aggregate;
}


void CLIParser::save(){

    database.write();
}

void CLIParser::help(){

    Message::Custom("You lost, huh?");
    std::unordered_set<std::string>::iterator it;

    std::cout << "List of available commands: " << std::endl;
    for(auto it: commands){

        std::cout << it << std::endl;
    }

    std::cout << "For more information, please refer to the following document:" << std::endl;
    std::cout << "https://docs.google.com/document/d/1quesENVOm28Ue37vGhU2oB4d-dsUG0VX1mCELxx6LN4/edit#heading=h.6yfyd6gy9ewc" << std::endl;
}


void CLIParser::send_show(){

    database.show_tables();

}

void CLIParser::exit(){

    exit_flag = true;
}
void CLIParser::save_as(std::string arg){

    database.write(arg);
}
void CLIParser::send_import(std::string arg){

    database.import_table(arg);
}

void CLIParser::send_describe(std::string arg){

    database.describe_table(arg);
}

void CLIParser::send_print(std::string arg){

    database.print_table(arg);
}

void CLIParser::send_rename(std::string arg1, std::string arg2){

    database.rename_table(arg1, arg2);
}

void CLIParser::send_export(std::string arg1, std::string arg2){

    database.export_table(arg1, arg2);

}

void CLIParser::send_delete(std::string arg1, int arg2, Record* arg3){

    database.delete_rows(arg1, arg2, arg3);
}

void CLIParser::send_count(std::string arg1, int arg2, Record* arg3){

    database.count_cols(arg1, arg2, arg3);
}

void CLIParser::send_select(std::string arg1, int arg2, Record* arg3){

    database.select_rows(arg1, arg2, arg3);

}

void CLIParser::send_add_column(std::string arg1, std::string arg2, Type type){

    database.add_empty_column(arg1, arg2, type);

}

void CLIParser::send_innerjoin(std::string arg1, int col1, std::string arg2, int col2){

    database.innerjoin(arg1, col1, arg2, col2);
}

void CLIParser::send_update(std::string arg1, int col1, Record* rec1, int col2, Record* rec2){

    database.update_column(arg1, col1, rec1, col2, rec2);
}

void CLIParser::send_insert(std::string arg1, std::vector<Record*> recs){

    database.insert(arg1, Row(recs));
}

void CLIParser::send_aggregate(std::string arg1, int col1, Record* rec, int col2, std::string arg2){

    database.aggregate(arg1, col1, rec, col2, arg2);
}

void CLIParser::parse_noargs(std::string action, std::vector<std::string> args){

    command_to_func_noargs[action]();
}


void CLIParser::parse_s(std::string action, std::vector<std::string> args){

    if(args.size() < 1){

        Message::InvalidInput();
        return;
    }

    command_to_func_s[action](args[0]);
    
}

void CLIParser::parse_ss(std::string action, std::vector<std::string> args){

    if(args.size()<2){

        Message::InvalidInput();
        return;
    }

    command_to_func_ss[action](args[0], args[1]);

}

void CLIParser::parse_sir(std::string action, std::vector<std::string> args){

    if(args.size()<3){

        Message::InvalidInput();
        return;
    }

    int val;
    Record* rec;

    try{

        val = parse_int(args[1]);
        rec = parse_rec(args[2]);
    }

    catch(int err){

        Message::InvalidInput();
        return;
    }

    command_to_func_sir[action](args[0], val, rec);
}

void CLIParser::parse_sst(std::string action, std::vector<std::string> args){

    if(args.size() < 3){

        Message::InvalidInput();
        return;
    }

    int type_val;

    try{

        type_val = parse_int(args[2]);
        
    }

    catch(int err){

        Message::InvalidInput();
        return;
    }

    if(type_val > 2){

        Message::InvalidInput();
        return;
    }

    Type type = static_cast<Type>(type_val);

    command_to_func_sst[action](args[0], args[1], type);
}

void CLIParser::parse_sisi(std::string action, std::vector<std::string> args){

    if(args.size()<4){

        Message::InvalidInput();
        return;
    }

    int col1, col2;

    try{

        col1 = parse_int(args[1]);
        col2 = parse_int(args[3]);
    }

    catch(int err){

        Message::InvalidInput();
        return;
    }

    command_to_func_sisi[action](args[0], col1, args[2], col2);
}

void CLIParser::parse_sirir(std::string action, std::vector<std::string> args){

    if(args.size() < 5){

        Message::InvalidInput();
        return;
    }

    Record* rec1;
    Record* rec2;
    int col1;
    int col2;

    try{

        col1 = parse_int(args[1]);
        col2 = parse_int(args[3]);

        rec1 = parse_rec(args[2]);
        rec2 = parse_rec(args[4]);
    }

    catch(int err){

        Message::InvalidInput();
        return;
    }

    command_to_func_sirir[action](args[0], col1, rec1, col2, rec2);

}

void CLIParser::parse_sv(std::string action, std::vector<std::string> args){

    if(args.size()<2){

        Message::InvalidInput();
        return;

    }

    std::vector<Record*> recs;

    for(int i=1; i<args.size(); i++){

        Record* rec;
        try{

            rec = parse_rec(args[i]);
            recs.push_back(rec);

        }

        catch(int err){

            Message::InvalidInput();
            return;
        }
    }

    command_to_func_sv[action](args[0], recs);
}

void CLIParser::parse_siris(std::string action, std::vector<std::string> args){

    if(args.size()<5){

        Message::InvalidInput();
        return;
    }

    int col1, col2;
    Record* rec;

    try{

        col1 = parse_int(args[1]);
        col2 = parse_int(args[3]);
        rec = parse_rec(args[2]);
        
    }

    catch(int err){

        Message::InvalidInput();
        return;
    }

    command_to_func_siris[action](args[0], col1, rec, col2, args[4]);
}

int CLIParser::parse_int(std::string val){

    std::stringstream ss(val);
    int res;
    ss >> res;

    if(ss.fail()) throw -1;
    return res;

}

Record* CLIParser::parse_rec(std::string arg){

    Record* rec = Caster::string_to_rec(arg);

    if(*rec == *(new RecordInvalid())){

        throw -1;
    }

    return rec;
}