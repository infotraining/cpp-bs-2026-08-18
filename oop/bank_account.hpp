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
        // constructors
        BankAccount(uint32_t id); 
        BankAccount(uint32_t account_id, double account_balance);

        uint32_t get_id() const
        {
            return id;
        }

        double get_balance() const
        {
            return balance;
        }

        void deposit(double amount);
        void withdraw(double amount);
        void print() const;
        
    private:
        uint32_t id;
        double balance = 0.0;
    };
} // namespace Banking

#endif // BANK_ACCOUNT_HPP