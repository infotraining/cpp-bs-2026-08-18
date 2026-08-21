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
            return id_;
        }

        double get_balance() const
        {
            return balance_;
        }

        static void set_interest_rate(double interest_rate)
        {
            interest_rate_ = interest_rate;
        }

        static double get_interest_rate()
        {
            return interest_rate_;
        }

        void pay_interest(int days = 1)
        {
            double interest = balance_ * interest_rate_ * (days / 365.0);
            balance_ += interest;
        }

        void deposit(double amount);
        void withdraw(double amount);
        void print() const;

    private:
        const uint32_t id_;
        double balance_ = 0.0;
        static double interest_rate_;
    };
} // namespace Banking

#endif // BANK_ACCOUNT_HPP