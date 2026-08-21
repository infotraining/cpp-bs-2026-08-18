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

        CHECK(account.get_id() == 12345);

        account.print();
    }

	SECTION("id & balance")
	{
		BankAccount account(12345, 1'000);

		CHECK(account.get_id() == 12345);
		CHECK(account.get_balance() == 1'000);

		account.print();
	}
}

TEST_CASE("BankAccount - balance")
{
    Banking::BankAccount account(12345);

    CHECK(account.get_balance() == 0.0);

    account.print();
}

TEST_CASE("BankAccount - deposit")
{
	BankAccount account(12345, 100);
	
	//account.balance += 100;
	account.deposit(100.0);

	CHECK(account.get_balance() == 200);

	account.print();
}

TEST_CASE("BankAccount - withdraw")
{
	BankAccount account(12345, 100);

	account.withdraw(50.5);

	CHECK(account.get_balance() == 49.5);

	account.print();
}

TEST_CASE("BankAccount - encapsulation")
{
	BankAccount account(12345, 100);

	account.deposit(100.0);
	account.deposit(40.0);
	account.deposit(1.0);
	account.withdraw(45.0);

	CHECK(account.get_balance() == 196.0);
}

TEST_CASE("BankAccount - daily interest rate")
{
	BankAccount::set_interest_rate(0.1); // call static function

	CHECK(BankAccount::get_interest_rate() == 0.1);

	BankAccount account(12345, 100.0);
	account.pay_interest(365);

	CHECK(account.get_balance() == 110.0);
}