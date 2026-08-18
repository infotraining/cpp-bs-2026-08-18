#include <iostream>

int global_variable = 42;
int counter = 0;

void do_something()
{
    int number = 665; // local variable

    std::cout << "Global variable: " << global_variable << std::endl;
    std::cout << "Local variable: " << number << std::endl;
}

int main()
{
    {
        int local_variable = 10;

        do_something();

        std::cout << "Global variable: " << global_variable << std::endl;
        std::cout << "Local variable: " << local_variable << std::endl;
    }

    //std::cout << "Local variable: " << local_variable << std::endl;

    std::cout << "Hello World!" << std::endl;
    return 0;
}