#include "Employee.hpp"
#include <print>

namespace records
{
   using namespace std;

   Employee::Employee(const string &firstName, const string &lastName) :
       firstName_{firstName},
       lastName_{lastName}
   {
   }

   void Employee::promote(int raiseAmount)
   {
      setSalary(getSalary() + raiseAmount);
   }

   void Employee::demote(int demeritAmount)
   {
      setSalary(getSalary() - demeritAmount);
   }

   void Employee::hire()
   {
      hired_ = true;
   }

   void Employee::fire()
   {
      hired_ = false;
   }

   void Employee::display() const
   {
      println("Employee: {}, {}", getLastName(), getFirstName());
      println("-------------------------");
      println("{}", (isHired() ? "Current Employee" : "Former Employee"));
      println("Employee Number: {}", getEmployeeNumber());
      println("Salary: ${}", getSalary());
      println("");
   }

   // Getters and setters
   void Employee::setFirstName(const string &firstName)
   {
      firstName_ = firstName;
   }

   const string &Employee::getFirstName() const
   {
      return firstName_;
   }

   void Employee::setLastName(const string &lastName)
   {
      lastName_ = lastName;
   }

   const string &Employee::getLastName() const
   {
      return lastName_;
   }

   void Employee::setEmployeeNumber(int employeeNumber)
   {
      employeeNumber_ = employeeNumber;
   }

   int Employee::getEmployeeNumber() const
   {
      return employeeNumber_;
   }

   void Employee::setSalary(int salary)
   {
      salary_ = salary;
   }

   int Employee::getSalary() const
   {
      return salary_;
   }

   bool Employee::isHired() const
   {
      return hired_;
   }
}