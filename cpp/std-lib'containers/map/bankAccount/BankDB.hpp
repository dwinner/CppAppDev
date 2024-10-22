#pragma once

#include <map>
#include <string>
#include <string_view>
#include "BankAccount.hpp"

class BankDB final
{
public:
   // Adds account to the bank database. If an account exists already
   // with that account number, the new account is not added. Returns true
   // if the account is added, false if it's not.
   bool addAccount(const BankAccount &account);

   // Removes the account with accountNumber from the database.
   void deleteAccount(int accountNumber);

   // Returns a reference to the account represented
   // by its account number or the client name.
   // Throws out_of_range if the account is not found.
   BankAccount &findAccount(int accountNumber);

   BankAccount &findAccount(std::string_view name);

   // Adds all the accounts from db to this database.
   // Deletes all the accounts from db.
   void mergeDatabase(BankDB &db);

private:
   std::map<int, BankAccount> accounts_;
};
