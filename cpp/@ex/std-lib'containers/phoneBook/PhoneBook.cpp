#include <format>
#include "PhoneBook.hpp"
#include "NoSuchPerson.hpp"

PhoneBook::PhoneBook() = default;

bool PhoneBook::addPhoneNum(const Person &aPerson, const std::string &aPhoneNum)
{
   if (!phoneBook_.contains(aPerson))
   {
      phoneBook_.insert({aPerson, std::make_unique<phoneVec>()});
   }

   phoneBook_[aPerson]->push_back(aPhoneNum);

   return true;
}

bool PhoneBook::removePhoneNum(const Person &aPerson, const std::string &aPhoneNum)
{
   if (phoneBook_.contains(aPerson))
   {
      std::erase(*phoneBook_[aPerson], aPhoneNum);
      return true;
   }

   return false;
}

const std::vector<std::string> &PhoneBook::getPhoneNums(const Person &aPerson)
{
   if (!phoneBook_.contains(aPerson))
   {
      auto errorMsg = std::format("There is no such person {}", (std::string) aPerson);
      throw NoSuchPerson{errorMsg};
   }

   return *(phoneBook_[aPerson]);
}
