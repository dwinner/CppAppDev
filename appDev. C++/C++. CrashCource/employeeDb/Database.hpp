#pragma once

#include <vector>
#include "Employee.hpp"

namespace Records
{
   class Database
   {
   public:
      Employee &addEmployee(const std::string &firstName, const std::string &lastName);

      Employee &getEmployee(int employeeNumber);

      [[maybe_unused]] Employee &getEmployee(const std::string &firstName, const std::string &lastName);

      void displayAll() const;

      void displayCurrent() const;

      void displayFormer() const;

   private:
      static const int FirstEmployeeNumber{1'000};

      std::vector<Employee> _employees;
      int _nextEmployeeNumber{FirstEmployeeNumber};
   };
}