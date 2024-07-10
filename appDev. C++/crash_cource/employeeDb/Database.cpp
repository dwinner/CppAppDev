#include <string>
#include "Database.hpp"

namespace Records
{
   Employee &Database::addEmployee(const std::string &firstName, const std::string &lastName)
   {
      Employee empToAdd{firstName, lastName};
      empToAdd.setEmployeeNumber(_nextEmployeeNumber++);
      empToAdd.hire();
      _employees.push_back(empToAdd);

      return _employees.back();
   }

   Employee &Database::getEmployee(int employeeNumber)
   {
      for (auto &employee: _employees)
      {
         if (employee.getEmployeeNumber() == employeeNumber)
         {
            return employee;
         }
      }

      throw std::logic_error{"No employee found."};
   }

   [[maybe_unused]] Employee &Database::getEmployee(const std::string &firstName, const std::string &lastName)
   {
      for (auto &employee: _employees)
      {
         if (employee.getFirstName() == firstName
             && employee.getLastName() == lastName)
         {
            return employee;
         }
      }

      throw std::logic_error{"No employee found."};
   }

   void Database::displayAll() const
   {
      for (const auto &employee: _employees)
      {
         employee.display();
      }
   }

   void Database::displayCurrent() const
   {
      for (const auto &employee: _employees)
      {
         if (employee.isHired())
         {
            employee.display();
         }
      }
   }

   void Database::displayFormer() const
   {
      for (const auto &employee: _employees)
      {
         if (!employee.isHired())
         {
            employee.display();
         }
      }
   }
}