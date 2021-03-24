#ifndef BRASS_SAMPLE_BRASS_H
#define BRASS_SAMPLE_BRASS_H

#include "AccountBase.h"

class Brass : public AccountBase
{
public:
   explicit Brass(const std::string& fullName = "Nullbody", long accountNumber = -1, double ballance = 0.0)
      : AccountBase(fullName, accountNumber, ballance)
   {
   }

   void withdraw(double ammount) override;

   void viewAccount() const override;

   ~Brass() override = default;
};

#endif //BRASS_SAMPLE_BRASS_H
