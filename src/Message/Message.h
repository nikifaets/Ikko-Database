#pragma once

#include <string>

class Message{

    public:
    static void FileNotFound(std::string filename);
    static void CorruptedTypeInformation(std::string filename);
    static void WrongDataType(int col_idx);
    static void CorruptedRow(int row_idx);
    static void WrongNumberOfColumns(int expected, int current);
    static void InvalidRecord(int col_idx);
};