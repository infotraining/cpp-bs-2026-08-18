#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

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

	SECTION("equals")
	{
		std::vector<int> vec = {1, 2, 3};
		std::list<int> lst = {1, 2, 3};

		CHECK(std::equal(vec.begin(), vec.end(), lst.begin(), lst.end()));
	}
}

TEST_CASE("reverse iterators")
{
	std::vector<int> vec = {1, 2, 3};

	for(auto it = vec.rbegin(); it != vec.rend(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << "\n";
}

TEST_CASE("algorithms with native arrays")
{
	int data[] = {1, 523, 3, 42, 534, 23, 33, -555, 534, 2323, 5, 23, 55, 0, 0, 1};

	std::sort(std::begin(data), std::end(data));

	for(int item : data)
		std::cout << item << " ";
	std::cout << "\n";
}

TEST_CASE("list")
{
	std::list<int> lst = {1, 2, 4, 5, 3};

	lst.push_back(6);
	lst.push_front(0);

	CHECK(lst == std::list<int>{0, 1, 2, 4, 5, 3, 6});

	// lst[1] = 3; // no indexing in list

	// but iterators can do ++ and --
	auto it = lst.begin();
	++it;

	CHECK(*it == 1);

	// std::sort(lst.begin(), lst.end()); // ERROR - list is not compatible with std::sort

	lst.sort(); // but lst.sort() is allowed
	CHECK(lst == std::list<int>{0, 1, 2, 3, 4, 5, 6});
}

TEST_CASE("std::pair")
{
	std::pair<int, std::string> p1{42, "forty-two"};

	CHECK(p1.first == 42);
	CHECK(p1.second == "forty-two");

	p1 = std::make_pair(8, "eight");
}

TEST_CASE("std::map")
{
	SECTION("basic usage")
	{
		std::map<int, std::string> dict = { {1, "one"}, {2, "two"}, {3, "three"} };
		
		std::map<int, std::string>::iterator pos = dict.find(2);

		if (pos != dict.end())
		{
			std::cout << "Znalazłem szukany element: (" << pos->first << ", " << pos->second << ")\n";
		}

		std::cout << "3: " << dict[3] << "\n";

		dict[4] = "four";
		std::cout << "4: " << dict[4] << "\n";

		dict.insert(std::make_pair(5, "five"));
		dict.emplace(7, "seven");
	}

	SECTION("handling duplicates")
	{
		std::map<int, std::string> dict = { {1, "one"}, {2, "two"}, {3, "three"} };

		// std::pair<std::map<int, std::string>::iterator, bool> result = dict.insert(std::make_pair(2, "dwa"));
		auto [pos, was_inserted] = dict.insert(std::make_pair(2, "dwa"));

		if (was_inserted)
		{
			std::cout << "Wstawiono: {" << pos->first << " : " << pos->second << "}\n";
		}
		else
		{
			std::cout << "Nie wstawiono nic. Klucz istnieje w mapie. " << pos->first << " : " << pos->second << "\n";
		}

		CHECK(dict[2] == "two");

		dict.insert_or_assign(2, "dwa");

		CHECK(dict[2] == "dwa");
	}
}