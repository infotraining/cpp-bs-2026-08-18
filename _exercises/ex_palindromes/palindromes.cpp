#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace ver_1
{
    bool is_palindrome(const std::string& text)
    {
        // abc|cba

        for (int i = 0; i < (text.length() / 2); i++)
        {
            char left = text[i];
            const int index_right = text.length() - 1 - i;
            char right = text[index_right];

            if (left != right)
            {
                return false;
            }
        }

        return true;
    }
} // namespace ver_1

bool is_palindrome(const std::string& text)
{
	const int middle = text.length() / 2;
    return std::equal(text.begin(), text.begin() + middle, text.rbegin());
}

TEST_CASE("palindromes")
{
    SECTION("is palindrome")
    {
        SECTION("empty string")
        {
            REQUIRE(is_palindrome(""));
        }

        SECTION("short")
        {
            std::string str = "potop";
            REQUIRE(is_palindrome(str));
        }

        SECTION("long")
        {
            std::string str = "lapalzakranakanarkazlapal";
            REQUIRE(is_palindrome(str));
        }
    }

    SECTION("is not palindrome")
    {
        std::string str = "mars";

        REQUIRE_FALSE(is_palindrome(str));
    }
}
