#include "bank_account.hpp"

namespace Banking
{
    double BankAccount::interest_rate_ = 0.1;

    BankAccount::BankAccount(uint32_t id)
        : id_(id) // lista inicjalizacji
    {
    }

    BankAccount::BankAccount(uint32_t id, double balance)
        : id_(id), balance_(balance)
    {
    }

    void BankAccount::deposit(double amount)
    {
        assert(amount > 0);
        balance_ += amount;
    }

    void BankAccount::withdraw(double amount)
    {
        assert(amount > 0);
        balance_ -= amount;
    }

    void BankAccount::print() const
    {
        std::cout << "BankAccount(id: " << id_ << "; balance: " << balance_ << ")\n";
    }
} // namespace Banking