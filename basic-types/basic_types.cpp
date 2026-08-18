#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std::literals;

TEST_CASE("integers")
{
    SECTION("raw-types")
    {
        int x = 10;
        int y = 10;
        unsigned int z = 10u;
        char small_number = 65;
        unsigned char small_unsigned_number = 255;
        long long big_number = 1000000000000ll;
        unsigned long long big_unsigned_number = 1000000000000ull;
    }

    SECTION("type-aliases")
    {
        int8_t small_number = 65;                        // char
        uint8_t small_unsigned_number = 255;             // unsigned char
        int16_t medium_number = 10000;                   // short
        uint16_t medium_unsigned_number = 10000u;        // unsigned short
        int32_t number = 100000;                         // int
        uint32_t unsigned_number = 100000u;              // unsigned int
        int64_t big_number = 1000000000000ll;            // long long
        uint64_t big_unsigned_number = 1000000000000ull; // unsigned long long

        intmax_t max_number = 1000000000000ll;            // long long
        uintmax_t max_unsigned_number = 1000000000000ull; // unsigned long

        CHECK(std::numeric_limits<int>::max() == 2'147'483'647);
        CHECK(std::numeric_limits<uintmax_t>::max() == 18'446'744'073'709'551'615);
    }
}

TEST_CASE("floating points")
{
    float f = 3.14f;
    double d = 3.14;

    CHECK(sizeof(f) == 4);
    CHECK(sizeof(double) == 8);
}

TEST_CASE("boolean values")
{
    bool flag = true;
    CHECK(flag);

    flag = false;
    CHECK(flag == false);
}

TEST_CASE("strings")
{
    SECTION("c-strings")
    {
        const char* c_string = "Hello, world!";
        const char* other_c_string = "text";

        std::cout << c_string << std::endl;
        std::cout << other_c_string << std::endl;

        // c_string[0] = 'h'; // ERROR
        // c_string += "!!"; // ERROR

        CHECK(std::strcmp(c_string, other_c_string) != 0);
    }

    SECTION("std::string")
    {
        std::string str1 = "Hello, world!";
        std::string str2 = "Text";

        std::cout << str1 << std::endl;
        std::cout << str2 << std::endl;

        str1[0] = 'h';
        str1 += "!!";

        CHECK(str1 == "hello, world!!!");

        std::string str3 = str1 + " " + str2;
        std::cout << str3 << std::endl;
    }
}

TEST_CASE("arrays")
{
    SECTION("c-arrays")
    {
        const int size = 10;
        int numbers[size] = {7, 543, 65, 32, 56, 77, 2, 5, -77, -1};
        
        numbers[0] = 10;

        for (int i = 0; i < size; ++i)
        {
            std::cout << numbers[i] << " ";
        }
        std::cout << std::endl;

        int min_value = std::numeric_limits<int>::max();

        for (int x = 0; x < size; x++)
        {
            if (numbers[x] < min_value)
            {
                min_value = numbers[x];
            }
        }

        CHECK(min_value == -77);

        std::cout << "Min value: " << min_value << std::endl;
    }

    SECTION("std::array")
    {
        std::array<int, 10> numbers = {7, 543, 65, 32, 56, 77, 2, 5, -77, -1};
        
        numbers[0] = 10;

        for (int i = 0; i < numbers.size(); ++i)
        {
            std::cout << numbers[i] << " ";
        }
        std::cout << std::endl;

        int min_value = std::numeric_limits<int>::max();

        for (int x = 0; x < numbers.size(); x++)
        {
            if (numbers[x] < min_value)
            {
                min_value = numbers[x];
            }
        }

        CHECK(min_value == -77);

        std::cout << "Min value: " << min_value << std::endl;
    }
}

TEST_CASE("vector")
{
    std::vector<int> numbers = {7, 543, 65, 32, 56, 77, 2, 5, -77, -1};
    CHECK(numbers.size() == 10);

    numbers[0] = 10;

    numbers.push_back(100);
    numbers.push_back(-100);

    for (int i = 0; i < numbers.size(); ++i)
    {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    int min_value = std::numeric_limits<int>::max();

    // for (int x = 0; x < numbers.size(); x++)
    // {
    //     if (numbers[x] < min_value)
    //     {
    //         min_value = numbers[x];
    //     }
    // }

    for (int n : numbers)
    {
        if (n < min_value)
        {
            min_value = n;
        }
    }

    CHECK(min_value == -77);

    std::cout << "Min value: " << min_value << std::endl;
}

TEST_CASE("range-based for loop")
{
    std::vector<std::string> words = {"Hello", "world", "from", "C++"};
    words.push_back("!!!");

    for(std::string word : words)
    {
        std::cout << word << "\n";
    }
}

TEST_CASE("reference types")
{
    int original = 10;
    original += 5;
    CHECK(original == 15);

    int& reference = original;
    reference += 15;
    CHECK(original == 30);

    std::string text = "Hello";
    std::string& text_reference = text;
    text_reference += ", world!";
    CHECK(text == "Hello, world!");
}

TEST_CASE("pointer types")
{
    int value = 42;
    std::cout << "Value: " << value << " is located at " << std::hex << &value << std::endl;

    int* pointer_to_value = &value;
    std::cout << "Pointer: " << pointer_to_value << " points to value: " << *pointer_to_value << std::endl;

    *pointer_to_value += 10;

    int* another_pointer = NULL; // legacy code
    int* yet_another_pointer = nullptr; // better way to initialize a pointer to null

    CHECK(another_pointer == nullptr);
    CHECK(another_pointer == 0);

    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int>* pointer_to_vec = &vec;
    pointer_to_vec->push_back(6); // (*pointer_to_vec).push_back(6);

    CHECK(vec == std::vector<int>{1, 2, 3, 4, 5, 6});

    // using pointers for iteration
    const int size = 5;
    int numbers[size] = {1, 2, 3, 4, 5};
    
    for(int* ptr_to_item = numbers; ptr_to_item != numbers + size; ++ptr_to_item)
    {
        std::cout << *ptr_to_item << "\n";
    }
}