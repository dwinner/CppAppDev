#pragma once

#include "Person.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class PhoneBook
{
   using phoneVec = std::vector<std::string>;

public:
   PhoneBook();

   bool addPhoneNum(const Person &aPerson, const std::string &aPhoneNum);

   bool removePhoneNum(const Person &aPerson, const std::string &aPhoneNum);

   const std::vector<std::string> &getPhoneNums(const Person &aPerson);

private:
   std::unordered_map<Person, std::unique_ptr<phoneVec>> phoneBook_;
};
