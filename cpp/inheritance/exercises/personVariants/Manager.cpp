#include "Manager.hpp"

namespace HR
{
   Manager::Manager(uint32_t employeeId) : Employee(employeeId)
   {}

   Manager::Manager(
       const std::string &firstName,
       const std::string &lastName,
       uint32_t employeeId) :
       Employee(firstName, lastName, employeeId)
   {}

   Manager::Manager(
       const std::string &firstName,
       const std::string &lastName,
       const std::string &initials,
       uint32_t employeeId) :
       Employee(firstName, lastName, initials, employeeId)
   {}

   std::string Manager::getClsName() const
   {
      return "Manager";
   }
}