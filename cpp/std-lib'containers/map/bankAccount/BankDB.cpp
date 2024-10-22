#include <stdexcept>
#include <format>
#include "BankDB.hpp"

bool BankDB::addAccount(const BankAccount &account)
{
   // Do the actual insert, using the account number as the key.
   auto res{accounts_.emplace(account.getAccountNumber(), account)};

   // or: auto res{ accounts_.insert(pair{ account.getAccountNumber(), account }) };

   // Without 'auto', you need the following:
   // Declare a variable to store the return from insert()
   //pair<map<int, BankAccount>::iterator, bool> res;
   // do the actual insert, using the account number as the key
   //res = accounts_.insert(make_pair(account.getAccountNumber(), account));

   // Return the bool field of the pair specifying success or failure.
   return res.second;
}

void BankDB::deleteAccount(int accountNumber)
{
   accounts_.erase(accountNumber);
}

BankAccount &BankDB::findAccount(int accountNumber)
{
   // Finding an element via its key can be done with find().
   auto it{accounts_.find(accountNumber)};

   // Without 'auto', you need:
   //map<int, BankAccount>::iterator it{ accounts_.find(accountNumber) };

   if (it == end(accounts_))
   {
      throw std::out_of_range{std::format("No account with number {}.", accountNumber)};
   }

   // Remember that iterators into maps refer to pairs of key/value.
   return it->second;
}

BankAccount &BankDB::findAccount(std::string_view name)
{
   // Finding an element by a non-key attribute requires a linear
   // search through the elements. The following uses structured bindings.
   for (auto &[accountNumber, account]: accounts_)
   {
      if (account.getClientName() == name)
      {
         return account;  // found it!
      }
   }

   // Without structured bindings:
   //for (auto& p : accounts_) {
   //	if (p.second.getClientName() == name) {
   //		return p.second;  // found it!
   //	}
   //}

   // Without range-based for loop:
   //for (map<int, BankAccount>::iterator it{ accounts_.begin() };
   //	it != accounts_.end(); ++it) {
   //	if (it->second.getClientName() == name) {
   //		return it->second;  // found it!
   //	}
   //}
   throw std::out_of_range{std::format("No account with name '{}'.", name)};
}

void BankDB::mergeDatabase(BankDB &db)
{
   // Use merge().
   accounts_.merge(db.accounts_);
   // Or: accounts_.insert(begin(db.accounts_), end(db.accounts_));

   // Now clear the source database.
   db.accounts_.clear();
}