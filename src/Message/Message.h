#pragma once

#include <string>

class Message{

    public:
    static void FileNotFound(std::string filename);
    static void NameTaken();
    static void CorruptedTypeInformation(std::string filename);
    static void WrongDataType(int col_idx);
    static void CorruptedRow(int row_idx);
    static void WrongNumberOfColumns(int expected, int current);
    static void InvalidRecord(int col_idx);
    static void CannotWriteFile(std::string filename);
    static void TableNotFound(std::string name);
    static void InvalidInput();
    static void Custom(std::string msg);
};