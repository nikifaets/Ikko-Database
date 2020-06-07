#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include "../Record/Record.h"
#include "../Database/Database.h"


class CLIParser{

    static Database database;
    static int parse_int(std::string val);
    static Record* parse_rec(std::string rec);
    static bool exit_flag;

    //parse and validate input of different type
    //s: string
    //i: integer
    //r: record
    static void parse_noargs(std::string action, std::vector<std::string> args);
    static void parse_s(std::string action, std::vector<std::string> args);
    static void parse_sir(std::string action, std::vector<std::string> args);
    static void parse_ss(std::string action, std::vector<std::string> args);
    static void parse_sst(std::string action, std::vector<std::string> args);
    static void parse_sisi(std::string action, std::vector<std::string> args);
    static void parse_sirir(std::string action, std::vector<std::string> args);
    static void parse_sv(std::string action, std::vector<std::string> args);
    static void parse_sisif(std::string action, std::vector<std::string> args);


    static const std::unordered_set<std::string> commands;

    //map to parser funcs
    static std::unordered_map<std::string, std::function<void(std::string, std::vector<std::string>)> > map_to_parser;
    static std::unordered_map<std::string, std::function<void(std::string, std::vector<std::string>)> > map_to_parser_sir;
    static std::unordered_map<std::string, std::function<void(std::string, std::vector<std::string>)> > map_to_parser_ss;
    //todo: all the others
    //map to sender funcs

    static std::unordered_map<std::string, std::function<void()> > command_to_func_noargs;
    static std::unordered_map<std::string, std::function<void(std::string)> >command_to_func_s;
    static std::unordered_map<std::string, std::function<void(std::string, std::string)> > command_to_func_ss;
    static std::unordered_map<std::string, std::function<void(std::string, int, Record*)> > command_to_func_sir;
    static std::unordered_map<std::string, std::function<void(std::string, std::string, Type)> > command_to_func_sst;
    static std::unordered_map<std::string, std::function<void(std::string, int, Record*, int, Record*)> >command_to_func_sirir;
    static std::unordered_map<std::string, std::function<void(std::string, std::vector<Record*>)> > command_to_func_sv;
    static std::unordered_map<std::string, std::function<void(std::string, int, std::string, int)> > command_to_func_sisi;
    //todo::agregate

    static void save();
    static void save_as(std::string arg);
    static void help();
    static void exit();

    static void send_show();
    static void send_import(std::string arg);
    static void send_describe(std::string arg);
    static void send_print(std::string arg);
    static void send_export(std::string arg1, std::string arg2);
    static void send_select(std::string arg1, int col, Record* rec);
    static void send_add_column(std::string arg1, std::string arg2, Type type);
    static void send_update(std::string arg1, int col1, std::string arg2, int col2, Record* rec);
    static void send_delete(std::string arg1, int col, Record* rec);
    static void send_insert(std::string arg1, std::vector<Record*> recs);
    static void send_innerjoin(std::string arg1, int col1, std::string arg2, int col2);
    static void send_rename(std::string arg1, std::string arg2);
    static void send_count(std::string arg1, int col, Record* rec);
    //static void send_aggregate(std::string)

    static void fill_maps();

    public:
    CLIParser();
    static void instantiate();
    static void parse();


};
