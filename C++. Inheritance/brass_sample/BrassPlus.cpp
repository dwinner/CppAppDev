#include "BrassPlus.h"

BrassPlus::BrassPlus(const std::string& fullName, long accountNumber, double ballance, double loan, double rate)
   : AccountBase(fullName, accountNumber, ballance)
{
   maxLoan_ = loan;
   owesBank_ = 0.0;
   rate_ = rate;
}

BrassPlus::BrassPlus(const Brass& brass, double maxLoan, double rate)
   : AccountBase(brass) // uses implicit copy constructor
{
   maxLoan_ = maxLoan;
   owesBank_ = 0.0;
   rate_ = rate;
}

void BrassPlus::viewAccount() const
{
   Formatting format = setFormat();

   using namespace std;

   cout << "BrassPlus Client: " << getFullName() << endl;
   cout << "Account Number: " << getAccountNumber() << endl;
   cout << "Balance: $" << getBalance() << endl;
   cout << "Maximum loan: $" << maxLoan_ << endl;
   cout << "Owed to bank: $" << owesBank_ << endl;
   cout.precision(3);
   cout << "Loan Rate: " << 100 * rate_ << "%\n";
   restore(format);
}

void BrassPlus::withdraw(double ammount)
{
   Formatting format = setFormat();

   using namespace std;

   double balance = getBalance();
   if (ammount <= balance)
   {
      AccountBase::withdraw(ammount);
   }
   else if (ammount <= balance + maxLoan_ - owesBank_)
   {
      double advance = ammount - balance;
      owesBank_ += advance * (1.0 + rate_);
      cout << "Bank advance: $" << advance << endl;
      cout << "Finance charge: $" << advance * rate_ << endl;
      deposit(advance);
      AccountBase::withdraw(ammount);
   }
   else
   {
      cout << "Credit limit exceeded. Transaction cancelled.\n";
   }

   restore(format);
}
