#include "bank_account.hpp"

namespace Banking
{
    BankAccount::BankAccount(uint32_t id)
    {
        this->id = id;
    }

    BankAccount::BankAccount(uint32_t account_id, double account_balance)
    {
        id = account_id;
        balance = account_balance;
    }

    void BankAccount::deposit(double amount)
    {
        assert(amount > 0);
        balance += amount;
    }

    void BankAccount::withdraw(double amount)
    {
        assert(amount > 0);
        balance -= amount;
    }

    void BankAccount::print() const
    {
        std::cout << "BankAccount(id: " << id << "; balance: " << balance << ")\n";
    }
} // namespace Banking