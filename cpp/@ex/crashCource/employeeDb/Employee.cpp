#include <string>
#include <ostream>
#include <format>
#include <iostream>
#include <utility>
#include "Employee.hpp"

namespace HR
{
   Employee::Employee(std::string firstName, std::string lastName, EmpType empType)
       : _firstName{std::move(firstName)},
         _lastName{std::move(lastName)},
         _empType{empType}
   {
   }

   void Employee::promote(int raiseAmount)
   {
      int oldSalary = getSalary();
      setSalary(oldSalary + raiseAmount);
   }

   [[maybe_unused]] void Employee::demote(int demeritAmount)
   {
      int oldSalary = getSalary();
      setSalary(oldSalary - demeritAmount);
   }

   void Employee::hire()
   {
      _hired = true;
   }

   void Employee::fire()
   {
      _hired = false;
   }

   void Employee::display() const
   {
      std::cout << std::format("Employee: {}, {}", getLastName(), getFirstName()) << std::endl;
      std::cout << std::format("-------------------------") << std::endl;
      std::cout << std::format("{}", (isHired() ? "Current Employee" : "Former Employee")) << std::endl;
      std::cout << std::format("Employee Number: {}", getEmployeeNumber()) << std::endl;
      std::cout << std::format("Salary: ${}", getSalary()) << std::endl;
      std::cout << std::format("Emp. type: {}", empTypeAsString()) << std::endl;
      std::cout << std::format("") << std::endl;
   }

   const std::string &Employee::getFirstName() const
   {
      return _firstName;
   }

   [[maybe_unused]] void Employee::setFirstName(const std::string &firstName)
   {
      _firstName = firstName;
   }

   const std::string &Employee::getLastName() const
   {
      return _lastName;
   }

   [[maybe_unused]] void Employee::setLastName(const std::string &lastName)
   {
      _lastName = lastName;
   }

   int Employee::getEmployeeNumber() const
   {
      return _employeeNumber;
   }

   void Employee::setEmployeeNumber(int employeeNumber)
   {
      _employeeNumber = employeeNumber;
   }

   int Employee::getSalary() const
   {
      return _salary;
   }

   void Employee::setSalary(int newSalary)
   {
      _salary = newSalary;
   }

   bool Employee::isHired() const
   {
      return _hired;
   }

   EmpType Employee::getEmpType() const
   {
      return _empType;
   }

   void Employee::setEmpType(EmpType empType)
   {
      _empType = empType;
   }

   std::string Employee::empTypeAsString() const
   {
      switch (_empType)
      {
         case EmpType::Engineer:
            return "Engineer";
         case EmpType::Senior:
            return "Senior";
         case EmpType::Manager:
            return "Manager";
         default:
            return "";
      }
   }
}
