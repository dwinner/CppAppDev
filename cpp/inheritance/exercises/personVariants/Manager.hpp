#pragma once

#include "Employee.hpp"

namespace HR
{
   class Manager : public Employee
   {
   public:
      explicit Manager(uint32_t employeeId);

      explicit Manager(
          const std::string &firstName,
          const std::string &lastName,
          uint32_t employeeId);

      explicit Manager(
          const std::string &firstName,
          const std::string &lastName,
          const std::string &initials,
          uint32_t employeeId);

      std::string getClsName() const override;
   };
}
