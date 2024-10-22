#pragma once

#include <string>

class BankAccount final
{
public:
   explicit BankAccount(int accountNumber, std::string name) :
       accountNumber_{accountNumber},
       clientName_{std::move(name)}
   {
   }

   void setAccountNumber(int accountNumber)
   {
      accountNumber_ = accountNumber;
   }

   int getAccountNumber() const
   {
      return accountNumber_;
   }

   void setClientName(std::string name)
   {
      clientName_ = std::move(name);
   }

   const std::string &getClientName() const
   {
      return clientName_;
   }

private:
   int accountNumber_;
   std::string clientName_;
};
