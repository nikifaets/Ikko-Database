#include "Message.h"
#include <iostream>

void Message::FileNotFound(std::string filename){

    std::cout << "No file can be found at address: " << std::endl << filename << std::endl;
}
