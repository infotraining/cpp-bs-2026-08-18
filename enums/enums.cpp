#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std::literals;

enum DayOfWeek { Mon = 1,
    Tue,
    Wed,
    Thd,
    Fri,
    Sat,
    Sun };

TEST_CASE("enums")
{
    SECTION("enum declaration and usage")
    {
        DayOfWeek day = Mon;

        if (day == Mon)
        {
            std::cout << "Jest poniedziałek\n";
        }
        else
        {
            std::cout << "Inny dzień tygodnia\n";
        }

        CHECK(day == Mon);
        CHECK(day == 1);
        CHECK(Sun == 7);

        switch (day)
        {
        case Mon:
            std::cout << "Poniedziałek\n";
            break;
        case Tue:
            std::cout << "Wtorek\n";
            break;
        case Wed:
            std::cout << "Środa\n";
            break;
        case Thd:
            std::cout << "Czwartek\n";
            break;
        case Fri:
            std::cout << "Piątek\n";
            break;
        default:
            std::cout << "Weekend\n";
            break;
        }
    }

    SECTION("enum to int conversion - implicit cast")
    {
        int day_number = Sun;
        CHECK(day_number == 7);
    }

    SECTION("int to enum conversion - explict cast")
    {
        int day_number = 3;
        DayOfWeek day = static_cast<DayOfWeek>(day_number);
        CHECK(day == Wed);
    }

    SECTION("enum in cout")
    {
        DayOfWeek day = Fri;
        std::cout << "Day of week: " << day << std::endl;
    }
}

// Since C++11, we can use scoped enumerations (enum class) to avoid implicit conversions and name clashes.

enum class Direction { Up,
    Down,
    Left,
    Right };

TEST_CASE("scoped enumerations")
{
    SECTION("enum class declaration and usage")
    {
        Direction current_direction = Direction::Up;

        if (current_direction == Direction::Up)
        {
            std::cout << "Going up!\n";
        }

        switch (current_direction)
        {
        case Direction::Up:
            std::cout << "Up\n";
            break;
        case Direction::Down:
            std::cout << "Down\n";
            break;
        case Direction::Left:
            std::cout << "Left\n";
            break;
        case Direction::Right:
            std::cout << "Right\n";
            break;
        }
    }

    SECTION("enum class to int conversion - explict cast")
    {
        Direction current_direction = Direction::Left;
        int direction_number = static_cast<int>(current_direction);
        CHECK(direction_number == 2); // Assuming Up=0, Down=1, Left=2, Right=3
    }

    SECTION("int to enum class conversion - explict cast")
    {
        int direction_number = 3;
        Direction current_direction = static_cast<Direction>(direction_number);
        CHECK(current_direction == Direction::Right);
    }

    SECTION("enum class in cout")
    {
        Direction current_direction = Direction::Down;
        std::cout << "Current direction: " << static_cast<int>(current_direction) << std::endl;
    }
}

void move_point(Direction move_direction, int& x, int& y)
{
    switch (move_direction)
    {
    case Direction::Up:
        y--;
        break;
    case Direction::Down:
        y++;
        break;
    case Direction::Left:
        x--;
        break;
    case Direction::Right:
        x++;
        break;
    }
}

TEST_CASE("enum class - exercise")
{
    int pos_x = 10;
    int pos_y = 20;

    SECTION("move up")
    {
        Direction move_direction = Direction::Up;

        move_point(move_direction, pos_x, pos_y);

        CHECK(pos_x == 10);
        CHECK(pos_y == 19);
    }

    SECTION("move left")
    {
        Direction move_direction = Direction::Left;

        move_point(move_direction, pos_x, pos_y);

        CHECK(pos_x == 9);
        CHECK(pos_y == 20);
    }

    SECTION("move down")
    {
        Direction move_direction = Direction::Down;

        move_point(move_direction, pos_x, pos_y);

        CHECK(pos_x == 10);
        CHECK(pos_y == 21);
    }

    SECTION("move right")
    {
        Direction move_direction = Direction::Right;

        move_point(move_direction, pos_x, pos_y);

        CHECK(pos_x == 11);
        CHECK(pos_y == 20);
    }
}

std::string enum_to_string(DayOfWeek dow)
{
    static const std::unordered_map<DayOfWeek, std::string> dict = {{Mon, "Monday"}, {Tue, "Tuesday"}, {Wed, "Wednesday"}, {Thd, "Thursday"}, {Fri, "Friday"}, {Sat, "Saturday"}, {Sun, "Sunday"}};

    return dict.at(dow);
}

TEST_CASE("enum to string mapping")
{
    DayOfWeek day = Wed;

    std::cout << "Today is: " << enum_to_string(day) << "\n";
}