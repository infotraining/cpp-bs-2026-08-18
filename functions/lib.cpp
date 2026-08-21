#include "lib.hpp"
#include <iostream>

void Lib::printf(const std::string& str)
{
    std::cout << "Another printf: " << str << std::endl;
}