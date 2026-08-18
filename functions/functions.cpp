#include "square.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

TEST_CASE("square")
{
    CHECK(MyMath::square(10) == 100);
}