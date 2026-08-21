#include <array>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

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

    for (std::string word : words)
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
    SECTION("basic pointer usage")
    {
        int value = 42;
        std::cout << "Value: " << value << " is located at " << std::hex << &value << std::endl;

        int* pointer_to_value = &value;
        std::cout << "Pointer: " << pointer_to_value << " points to value: " << *pointer_to_value << std::endl;

        *pointer_to_value += 10;

        CHECK(value == 52);
        CHECK(*pointer_to_value == 52);
    }

    SECTION("pointer initialization")
    {
        int* pointer_to_value = nullptr;     // the best way to initialize a pointer to zero
        int* yet_another_pointer_to_value{}; // value-initialized pointer, also nullptr

        // not-recommended ways to initialize a pointer to zero
        int* another_pointer = NULL; // legacy code
        int* one_more_pointer = 0;   // also valid, but not recommended

        CHECK(pointer_to_value == nullptr);
        CHECK(yet_another_pointer_to_value == nullptr);
        CHECK(another_pointer == nullptr);
        CHECK(another_pointer == 0);
    }

    SECTION("dereferencing a pointer")
    {
        int* pointer_to_value = nullptr;

        //*pointer_to_value = 42; // ERROR: dereferencing a nullptr - Undefined Behavior

        if (pointer_to_value) // check if the pointer is not nullptr
        {
            *pointer_to_value = 42; // OK: dereferencing a pointer only if it is not nullptr
        }
    }

    SECTION("pointer to vector")
    {
        std::vector<int> vec = {1, 2, 3, 4, 5};
        std::vector<int>* pointer_to_vec = &vec;
        pointer_to_vec->push_back(6); // (*pointer_to_vec).push_back(6);

        CHECK(vec == std::vector<int>{1, 2, 3, 4, 5, 6});
    }

    SECTION("pointer arithmetic")
    {
        const int size = 5;
        int numbers[size] = {1, 2, 3, 4, 5}, _;

        int* pointer_to_first_item = numbers; // &numbers[0]
        CHECK(*pointer_to_first_item == 1);

        int* pointer_to_last_item = numbers + (size - 1); // &numbers[size - 1]
        CHECK(*pointer_to_last_item == 5);

        int* pointer_to_middle = numbers + (size / 2);
        CHECK(*pointer_to_middle == 3);

        std::cout << "First item: " << *pointer_to_first_item << std::endl;
        std::cout << "Last item: " << *pointer_to_last_item << std::endl;

        pointer_to_first_item++;
        pointer_to_last_item--;

        std::cout << "Next item: " << *pointer_to_first_item << std::endl;
        std::cout << "Previous item: " << *pointer_to_last_item << std::endl;
    }

    SECTION("iteration using pointers")
    {
        const int size = 5;
        int numbers[size] = {1, 2, 3, 4, 5};

        for (int* it = numbers; it != numbers + size; ++it)
        {
            std::cout << *it << "\n";
        }
    }
}

TEST_CASE("finding min using pointers")
{
    const int size = 10;
    int numbers[size] = {1, -6, 99, -42, 5, 2, 3, 4, 5};

    int* pointer_to_min = &numbers[0];
    for (int* it = numbers; it != numbers + size; ++it)
    {
        if (*it < *pointer_to_min)
        {
            pointer_to_min = it;
        }
    }

    CHECK(*pointer_to_min == -42);

    *pointer_to_min = 665;
    CHECK(numbers[3] == 665);
}

TEST_CASE("const")
{
    SECTION("mutable variable")
    {
        int value = 42;
        value += 2;
        CHECK(value == 44);
    }

    SECTION("immutable variable")
    {
        const int value = 665;
        //++value; // ERROR: value is const
        CHECK(value == 665);
    }

    SECTION("const reference")
    {
        int value = 42;
        ++value;

        const int& const_ref_to_value = value;
        CHECK(const_ref_to_value == 43);

        // const_ref_to_value = 665; // ERROR: ref to const
    }

    SECTION("const with pointers")
    {
        int value = 42;
        int other_value = 665;

        SECTION("pointer to const")
        {
            const int* pointer_to_const = &value;
            CHECK(*pointer_to_const == 42);
            // *pointer_to_const = 43; // ERROR: cannot change value under the pointer

            pointer_to_const = &other_value; // redirecting a pointer to a new memory location
            CHECK(*pointer_to_const == 665);
        }

        SECTION("const pointer to variable")
        {
            int* const const_pointer_to_value = &value;
            // const_pointer_to_value = &other_value; // ERROR: cannot change address inside const pointer
            *const_pointer_to_value = 777;
            CHECK(value == 777);
        }

        SECTION("const pointer to const")
        {
            const int* const const_ptr_to_const = &value;
            // *const_ptr_to_const = 888;  // ERROR
            // const_ptr_to_const = &other_value; // ERROR
        }
    }
}

struct Point
{
    int x;
    int y;

    // method to move the point by dx and dy
    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    void print() const
    {
        std::cout << "Point(" << x << ", " << y << ")\n";
    }
};

TEST_CASE("structs")
{
    Point position{10, 20};

    CHECK(position.x == 10);
    CHECK(position.y == 20);

    position.x += 5;
    position.y += 10;

    CHECK(position.x == 15);
    CHECK(position.y == 30);

    Point another_position = position; // copying the object position to another_position
    CHECK(another_position.x == 15);
    CHECK(another_position.y == 30);
}

TEST_CASE("structs with methods")
{
    Point position{10, 20};
    position.print();

    position.move(5, 10);
    position.print();

    CHECK(position.x == 15);
    CHECK(position.y == 30);
}
void draw_all_points(const std::vector<Point>& points)
{
    for (const Point& p : points)
    {
        p.print();
    }
}

TEST_CASE("polygon")
{
    std::vector<Point> polygon = { Point{0, 0}, Point{10, 0}, Point{10, 10}, Point{0, 10} };

    for (int i = 0; i < polygon.size(); i++)
    {
        polygon[i].print();
    }

    std::cout << "Moving the polygon by (5, 5)\n";

    // range-based for - modifying the points in the polygon
    for(Point& p : polygon)
    {
        p.move(5, 5);
    }

    draw_all_points(polygon);
}