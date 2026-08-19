#include "square.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <optional>

using namespace std::literals;

using namespace MyMath;

TEST_CASE("square")
{
    CHECK(MyMath::square(10) == 100);
    CHECK(square(2.1) == 4.41);
}

int power(int n)
{
    std::cout << "Evil power!!!\n";
    return 665;
}

TEST_CASE("power")
{
    CHECK(power(2, 3) == 8);
    CHECK(power(5, 0) == 1);
    CHECK(power(3, 4) == 81);

    CHECK(MyMath::power(2) == 2); // default exponent = 1
    CHECK(::power(42) == 665);
}

void f_arg_by_value(int x)
{
    std::cout << "Value of x: " << x << std::endl;
    x = 42;
    std::cout << "Value of x after modification: " << x << std::endl;
}

TEST_CASE("passing arguments by value")
{
    int a = 10;
    std::cout << "Before calling f: " << a << std::endl;
    f_arg_by_value(a);
    std::cout << "After calling f: " << a << std::endl;

    CHECK(a == 10); // a remains unchanged
}

void f_arg_by_reference(int& x)
{
    std::cout << "Value of x: " << x << std::endl;
    x = 42;
    std::cout << "Value of x after modification: " << x << std::endl;
}

TEST_CASE("passing arguments by reference")
{
    int a = 10;
    std::cout << "Before calling f: " << a << std::endl;
    f_arg_by_reference(a);
    std::cout << "After calling f: " << a << std::endl;

    CHECK(a == 42); // a is modified
}

void print(const std::vector<int>& vec, const std::string& desc)
{
    std::cout << desc << ": ";
    for(int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }

    std::cout << "\n";
}

TEST_CASE("passing arguments by const reference")
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    print(vec, "vec");

    vec.push_back(7);
    print(vec, "vec");
}


std::optional<int> get_min_value(const std::vector<int>& vec)
{
    if (vec.empty())
        return std::nullopt;

    int min_value = std::numeric_limits<int>::max();
    
    for(int item : vec)
    {
        if (item < min_value)
            min_value = item;
    }

    return min_value;
}

TEST_CASE("get_min_value")
{
    std::vector<int> vec = {21, 534, 94, 1, 245, 53, 534, 534};
    std::optional<int> min_value = get_min_value(vec);
    CHECK(min_value.has_value() == true);
    CHECK(*min_value == 1);
    CHECK(min_value.value() == 1);

    std::vector<int> empty_vec;
    min_value = get_min_value(empty_vec);
    CHECK(min_value.has_value() == false);

    std::vector<int> vec_with_max = {std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
    min_value = get_min_value(vec_with_max);
    CHECK(*min_value == std::numeric_limits<int>::max());
}

TEST_CASE("optional")
{
    std::optional<int> opt_int = std::nullopt;
    CHECK(opt_int.has_value() == false);

    opt_int = 42;
    CHECK(opt_int.has_value() == true);

    CHECK(opt_int.value() == 42);
    
    if (opt_int)
        CHECK(*opt_int == 42);
}