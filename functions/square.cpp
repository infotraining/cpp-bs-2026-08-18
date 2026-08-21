#include <string>
#include <iostream>

#include "square.hpp"

namespace MyMath
{
    int square(int x)
    {
        return x * x;
    }

    double square(double x)
    {
        return x * x;
    }

    int power(int base, int exponent)
    {
        int result = 1;
        for (int i = 0; i < exponent; ++i)
        {
            result *= base;
        }
        return result;
    }

    double deg_to_rad(double degrees)
    {
        return degrees * (3.14159 / 180.0);
    }
} // namespace MyMath

using namespace std; // only in cpp file, not in header file

void MyMath::printf(const std::string& str)
{
    std::cout << "printf: " << str << std::endl;
}