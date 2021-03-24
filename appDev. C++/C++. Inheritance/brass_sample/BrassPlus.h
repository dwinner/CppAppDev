#ifndef BRASS_SAMPLE_BRASSPLUS_H
#define BRASS_SAMPLE_BRASSPLUS_H

#include "Brass.h"

class BrassPlus : public AccountBase
{
public:
   explicit BrassPlus(const std::string& fullName = "Nullbody", long accountNumber = -1,
                      double ballance = 0.0, double loan = 500,
                      double rate = 0.10);

   explicit BrassPlus(const Brass& brass, double maxLoan = 500, double rate = 0.1);

   void viewAccount() const override;

   void withdraw(double ammount) override;

   void resetMax(double maxLoan)
   {
      maxLoan_ = maxLoan;
   }

   void resetRate(double rate)
   {
      rate_ = rate;
   }

   void resetOwes()
   {
      owesBank_ = 0;
   }

private:
   double maxLoan_;
   double rate_;
   double owesBank_;
};


#endif //BRASS_SAMPLE_BRASSPLUS_H
