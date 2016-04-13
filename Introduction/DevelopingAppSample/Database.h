#pragma once

#include <iostream>
#include <vector>
#include "Employee.h"

namespace Records
{
   const int FirstEmployeeNumber = 1000;

   class Database
   {
   public:
      Database();
      ~Database();

      Employee& addEmployee(std::string aFirstName, std::string aLastName);
      Employee& getEmployee(int anEmployeeNumber);
      Employee& getEmployee(std::string aFirstName, std::string aLastName);

      void displayAll() const;
      void displayCurrent() const;
      void displayFormer() const;

   protected:
      std::vector<Employee> employees;
      int nextEmployeeNumber;
   };
}