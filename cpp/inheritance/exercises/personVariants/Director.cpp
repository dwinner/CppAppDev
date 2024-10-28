#include "Director.hpp"

namespace HR
{
   Director::Director(uint32_t employeeId) : Employee(employeeId)
   {}

   Director::Director(
       const std::string &firstName,
       const std::string &lastName,
       uint32_t employeeId) :
       Employee(firstName, lastName, employeeId)
   {}

   Director::Director(
       const std::string &firstName,
       const std::string &lastName,
       const std::string &initials,
       uint32_t employeeId) :
       Employee(firstName, lastName, initials, employeeId)
   {}

   std::string Director::getClsName() const
   {
      return "Director";
   }
}