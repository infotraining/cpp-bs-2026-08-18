#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <cstddef>
#include <cstdint>
#include <iostream>

namespace Banking
{
    struct BankAccount
    {
        uint32_t id;
        double balance = 0.0;

        // constructor to initialize the account with an ID
        BankAccount(uint32_t account_id) 
        {
            id = account_id;
        }

        BankAccount(uint32_t account_id, double account_balance)
        {
            id = account_id;
            balance = account_balance;
        }

        void print() const
        {
            std::cout << "BankAccount(id: " << id << "; balance: " << balance << ")\n";
        }
    };
} // namespace Banking

#endif // BANK_ACCOUNT_HPP