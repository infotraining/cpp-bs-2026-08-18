#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cassert>

namespace Banking
{
    class BankAccount
    {
    public:
        // constructor to initialize the account with an ID
        BankAccount(uint32_t id) 
        {
            this->id = id;
        }

        BankAccount(uint32_t account_id, double account_balance)
        {
            id = account_id;
            balance = account_balance;
        }

        uint32_t get_id() const
        {
            return id;
        }

        double get_balance() const
        {
            return balance;
        }

        void deposit(double amount)
        {
            assert(amount > 0);
            balance += amount;
        }

        void withdraw(double amount)
        {
            assert(amount > 0);
            balance -= amount;
        }

        void print() const
        {
            std::cout << "BankAccount(id: " << id << "; balance: " << balance << ")\n";
        }
    private:
        uint32_t id;
        double balance = 0.0;
    };
} // namespace Banking

#endif // BANK_ACCOUNT_HPP