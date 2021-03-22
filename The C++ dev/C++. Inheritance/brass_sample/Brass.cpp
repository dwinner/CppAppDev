#include "Brass.h"

void Brass::withdraw(double ammount)
{
   if (ammount < 0)
   {
      std::cout << "Withdrawal amount must be positive; withdrawal canceled.\n";
   }
   else if (ammount <= getBalance())
   {
      AccountBase::withdraw(ammount);
   }
   else
   {
      std::cout << "Withdrawal amount of $" << ammount
         << " exceeds your balance.\n"
         << "Withdrawal canceled.\n";
   }
}

void Brass::viewAccount() const
{
   Formatting formatting = setFormat();
   std::cout << "Brass Client: " << getFullName() << std::endl;
   std::cout << "Account Number: " << getAccountNumber() << std::endl;
   std::cout << "Balance: $" << getBalance() << std::endl;
   restore(formatting);
}
