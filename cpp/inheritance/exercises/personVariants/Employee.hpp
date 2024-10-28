#pragma once

#include <cstdint>
#include "Person.hpp"

namespace HR
{
   class Employee : public Person
   {
   public:
      explicit Employee(uint32_t employeeId);

      explicit Employee(
          const std::string &firstName,
          const std::string &lastName,
          uint32_t employeeId);

      inline uint32_t getEmployeeId() const;

      explicit Employee(
          const std::string &firstName,
          const std::string &lastName,
          const std::string &initials,
          uint32_t employeeId);

      std::string toString() const override;

      std::string getClsName() const override;

   private:
      uint32_t employeeId_;
   };
}
