#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

namespace LegacyCode
{
    double avg(const int* data, const int size)
    {
        double sum = 0.0;

        for (const int* ptr_item = data; ptr_item != data + size; ++ptr_item)
            sum += *ptr_item;

        return sum / size;
    }
} // namespace LegacyCode

namespace ModernCpp
{
    double avg(const std::vector<int>& data)
    {
        double sum = 0.0;

        for (int item : data)
        {
            sum += item;
        }

        return sum / data.size();
    }
} // namespace ModernCpp

TEST_CASE("avg")
{
    int data[] = {1, 2, 3, 4, 5};
    CHECK(LegacyCode::avg(data, 5) == 3.0);

    std::vector<int> vec = {1, 2, 3, 4, 5};
    CHECK(ModernCpp::avg(vec) == 3.0);
}

TEST_CASE("iterators")
{
    SECTION("native pointers are iterator")
    {
        const int size = 10;
        int tab[size] = {1, 2, 3, 4, 5, 6, 8};

        for (int* it = tab; it != tab + size; ++it)
            std::cout << *it << " ";
        std::cout << "\n";
    }

    SECTION("vector has iterators")
    {
        std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};

        std::vector<int>::iterator it = vec.begin();
        CHECK(*it == 1);

        ++it;
        CHECK(*it == 2);

        for (/*std::vector<int>::iterator*/ auto it = vec.begin(); it != vec.end(); ++it)
            std::cout << *it << " ";
        std::cout << "\n";
    }

    SECTION("array has iterators")
    {
        std::array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        std::array<int, 10>::iterator it = arr.begin();
        CHECK(*it == 1);

        for (/*std::array<int, 10>::iterator*/ auto it = arr.begin(); it != arr.end(); ++it)
            std::cout << *it << " ";
        std::cout << "\n";
    }

    SECTION("range-based for")
    {
        std::vector<int> vec = {1, 2, 3};

        for (int item : vec)
            std::cout << item << " ";
        std::cout << "\n";

        SECTION("is iterpreted as")
        {
            for (auto it = vec.begin(); it != vec.end(); ++it)
            {
                int item = *it;
                std::cout << item << " ";
            }
            std::cout << "\n";
        }
    }
}

TEST_CASE("basic algorithms")
{
    std::vector<int> vec = {1, 523, 3, 42, 534, 23, 33, -555, 534, 2323, 5, 23, 55, 0, 0, 1};

    SECTION("find")
    {
        SECTION("happy path - value is in vector")
        {
            std::vector<int>::iterator pos = std::find(vec.begin(), vec.end(), 42);
            CHECK(pos != vec.end());
            CHECK(*pos == 42);
        }

		SECTION("sad path - no value in vector")
		{
        	auto pos = std::find(vec.begin(), vec.end(), 665);
        	CHECK(pos == vec.end());
		}
    }

	SECTION("min_element")
	{
		auto pos_min = std::min_element(vec.begin(), vec.end());
		CHECK(*pos_min == -555);

		auto pos_max = std::max_element(vec.begin(), vec.end());
		CHECK(*pos_max == 2323);
	}

	SECTION("count")
	{
		CHECK(std::count(vec.begin(), vec.end(), 1) == 2);
	}

	SECTION("sort")
	{
		std::sort(vec.begin(), vec.end());

		CHECK(std::is_sorted(vec.begin(), vec.end()));

		for(int item : vec)
			std::cout << item << " ";
		std::cout << "\n";
	}

	SECTION("sort in descending order")
	{
		std::sort(vec.begin(), vec.end(), std::greater<int>{});

		for(int item : vec)
			std::cout << item << " ";
		std::cout << "\n";
	}

	SECTION("sorting first 5 items")
	{
		std::sort(vec.begin(), vec.begin() + 5);

		for(int item : vec)
			std::cout << item << " ";
		std::cout << "\n";

	}
}

TEST_CASE("algorithms with native arrays")
{
	int data[] = {1, 523, 3, 42, 534, 23, 33, -555, 534, 2323, 5, 23, 55, 0, 0, 1};

	std::sort(std::begin(data), std::end(data));

	for(int item : data)
		std::cout << item << " ";
	std::cout << "\n";
}