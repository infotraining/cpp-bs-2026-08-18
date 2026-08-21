#include "bank_account.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

using namespace Banking;

TEST_CASE("BankAccount - constructor")
{
    SECTION("only id")
    {
        BankAccount account(12345);

        account.id = 12345;
        CHECK(account.id == 12345);

        account.print();
    }

	SECTION("id & balance")
	{
		BankAccount account(12345, 1'000);

		CHECK(account.id == 12345);
		CHECK(account.balance == 1'000);

		account.print();
	}
}

TEST_CASE("BankAccount - balance")
{
    Banking::BankAccount account(12345);

    CHECK(account.balance == 0.0);

    account.balance = 100.50;
    CHECK(account.balance == 100.50);

    account.print();
}