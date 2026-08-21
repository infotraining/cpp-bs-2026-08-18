#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <string>

#define PI 3.14159

namespace MyMath
{
    int square(int x);       // declarations
    double square(double x); // overloaded function

    int power(int base, int exponent = 1);

    double deg_to_rad(double degrees);

    void printf(const std::string& str);
} // namespace MyMath

#endif // SQUARE_HPP