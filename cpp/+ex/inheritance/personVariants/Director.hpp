#pragma once

#include "Employee.hpp"

namespace HR
{
   class Director : public Employee
   {
   public:
      explicit Director(uint32_t employeeId);

      explicit Director(
          const std::string &firstName,
          const std::string &lastName,
          uint32_t employeeId);

      explicit Director(
          const std::string &firstName,
          const std::string &lastName,
          const std::string &initials,
          uint32_t employeeId);

      std::string getClsName() const override;
   };
}
