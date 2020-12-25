#include <iostream>
#include "AccountBase.h"

using std::cout;
using std::ios_base;
using std::endl;
using std::string;

AccountBase::AccountBase(const std::string& fullName, long accountNumber, double balance)
{
   fullName_ = fullName;
   accountNumber_ = accountNumber;
   balance_ = balance;
}

void AccountBase::deposit(double ammount)
{
   if (ammount < 0)
   {
      cout << "Negative deposit not allowed; deposit is cancelled.\n" << endl;
   }
   else
   {
      balance_ += ammount;
   }
}

void AccountBase::withdraw(double ammount)
{
   balance_ -= ammount;
}

AccountBase::Formatting AccountBase::setFormat() const
{
   // set up ###.## format
   Formatting formatting{};
   formatting.flag = cout.setf(ios_base::fixed, ios_base::floatfield);
   formatting.pr = cout.precision(2);

   return formatting;
}

void AccountBase::restore(Formatting& formatting) const
{
   cout.setf(formatting.flag, ios_base::floatfield);
   cout.precision(formatting.pr);
}
