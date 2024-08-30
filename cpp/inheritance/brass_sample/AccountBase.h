#ifndef BRASS_SAMPLE_ACCOUNTBASE_H
#define BRASS_SAMPLE_ACCOUNTBASE_H

#include <iostream>
#include <string>

// Abstract Base Class
class AccountBase
{
public:
   explicit AccountBase(const std::string& fullName = "Nullbody", long accountNumber = -1, double balance = 0.0);

   void deposit(double ammount);

   virtual void withdraw(double ammount) = 0; // pure virtual function

   double getBalance() const
   {
      return balance_;
   }

   virtual void viewAccount() const = 0; // pure virtual function

   virtual ~AccountBase() = default;

protected:
   struct Formatting
   {
      std::ios_base::fmtflags flag;
      std::streamsize pr;
   };

   const std::string& getFullName() const
   {
      return fullName_;
   }

   long getAccountNumber() const
   {
      return accountNumber_;
   }

   Formatting setFormat() const;

   void restore(Formatting& formatting) const;

private:
   std::string fullName_;
   long accountNumber_;
   double balance_;
};


#endif //BRASS_SAMPLE_ACCOUNTBASE_H
