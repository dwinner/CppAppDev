#include <format>
#include "Employee.hpp"

namespace HR
{
   Employee::Employee(uint32_t employeeId) :
       Person(), employeeId_(employeeId)
   {}

   Employee::Employee(
       const std::string &firstName,
       const std::string &lastName,
       uint32_t employeeId) :
       Person(firstName, lastName), employeeId_(employeeId)
   {}

   Employee::Employee(
       const std::string &firstName,
       const std::string &lastName,
       const std::string &initials,
       uint32_t employeeId) :
       Person(firstName, lastName, initials), employeeId_(employeeId)
   {}

   uint32_t Employee::getEmployeeId() const
   {
      return employeeId_;
   }

   std::string Employee::toString() const
   {
      std::string personObj = Person::toString();
      uint32_t empId = getEmployeeId();
      std::string empObj = std::format("{}, ID = {}", personObj, empId);

      return empObj;
   }

   std::string Employee::getClsName() const
   {
      return "Employee";
   }
}