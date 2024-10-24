#include <iostream>
#include <print>
#include "PhoneBook.hpp"
#include "NoSuchPerson.hpp"

using namespace std;

int main()
{
   try
   {
      PhoneBook phoneBook;

      Person me = "Den Win"_p;
      phoneBook.addPhoneNum(me, "89529629971");
      phoneBook.addPhoneNum(me, "89539629081");
      phoneBook.addPhoneNum(me, "89109626996");

      const char *emergencyNum = "911";
      phoneBook.addPhoneNum(me, emergencyNum);
      phoneBook.removePhoneNum(me, emergencyNum);

      me.output(cout);
      cout << endl;
      for (const auto &phoneItem: phoneBook.getPhoneNums(me))
      {
         println("{}", phoneItem);
      }

      Person other{"John", "Doe"};
      auto invalidNums = phoneBook.getPhoneNums(other);
      for (const auto &phoneItem: invalidNums)
      {
         println("{}", phoneItem);
      }
   }
   catch (const NoSuchPerson &noSuchError)
   {
      println("{}", noSuchError.what());
   }
}
