#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

namespace MyMath
{
    bool is_prime(int number)
    {
        for (int n = 2; n <= std::sqrt(number); ++n)
        {
            if (number % n == 0)
                return false;
        }

        return true;
    }
} // namespace MyMath

TEST_CASE("is_prime")
{
    using namespace MyMath;

    REQUIRE(is_prime(2));
    REQUIRE(is_prime(3));
    REQUIRE_FALSE(is_prime(4));
    REQUIRE(is_prime(5));
    REQUIRE_FALSE(is_prime(6));
    REQUIRE(is_prime(13));
    REQUIRE_FALSE(is_prime(14));
    REQUIRE(is_prime(59));
    REQUIRE(is_prime(997));
}

namespace MyMath
{
    std::vector<int> primes(int n)
    {
        std::vector<int> found_primes;

        for (int number = 2; number <= n; ++number)
        {
            if (is_prime(number))
                found_primes.push_back(number);
        }

        return found_primes;
    }
} // namespace MyMath

TEST_CASE("find all primes in range [2;n]")
{
    using namespace MyMath;
    REQUIRE(primes(10) == std::vector<int>{2, 3, 5, 7});
    REQUIRE(primes(20) == std::vector<int>{2, 3, 5, 7, 11, 13, 17, 19});

	std::vector<int> primes_up_to_1000 = primes(1000);

	for(int p : primes_up_to_1000)
		std::cout << p << " ";
	std::cout << "\n";
}