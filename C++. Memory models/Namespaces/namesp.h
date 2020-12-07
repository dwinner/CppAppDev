#ifndef NAMESPACES_NAMESP_H
#define NAMESPACES_NAMESP_H

#include <string>

// create the pers and debts namespaces
namespace pers
{
   struct Person
   {
      std::string fname;
      std::string lname;
   };

   void getPerson(Person &);

   void showPerson(const Person &);
}

namespace debts
{
   using namespace pers;
   struct Debt
   {
      Person name;
      double amount{};
   };

   void getDebt(Debt &);

   void showDebt(const Debt &);

   double sumDebts(const Debt ar[], int n);
}


#endif //NAMESPACES_NAMESP_H
