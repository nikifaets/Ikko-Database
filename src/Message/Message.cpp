#include "Message.h"
#include <iostream>

void Message::FileNotFound(std::string filename){

    std::cout << "No file can be found at address: " << std::endl << filename << std::endl;
}

void Message::CorruptedTypeInformation(std::string filename){

    std::cout << "The following file has corrupted information concerning the table's data types:" << std::endl;
    std::cout << filename << std::endl;
}

void Message::WrongDataType(int col_idx){

    std::cout << "Wrong data type at column " << col_idx << std::endl;
}

void Message::CorruptedRow(int row_idx){

    std::cout << "Corrupted row with index " << row_idx << std::endl;
}

void Message::WrongNumberOfColumns(int expected, int current){

    std::cout << "Row has " << current << " columns, but expected are " << expected << std::endl;

}

void Message::InvalidRecord(int col_idx){

    std::cout << "Invalid record at column " << col_idx << std::endl;
}

void Message::NameTaken(){

    std::cout << "The name is already in use.";
}

void Message::CannotWriteFile(std::string filename){

    std::cout << "Cannot open file to write: " + filename;
}

void Message::Custom(std::string msg){

    std::cout << msg << std::endl;
}

void Message::TableNotFound(std::string name){

    std::cout << "Cannot find table with name " + name << std::endl;
}

void Message::InvalidInput(){

    std::cout << "Input is invalid. " << std::endl;
}