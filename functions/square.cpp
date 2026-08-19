#include "square.hpp"

int square(int x) // definition
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