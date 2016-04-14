#include "stdafx.h";
#include <iostream>
#include "Employee.h"
#include <string>

using namespace std;

namespace Records
{
   Employee::Employee()
      : firstName(""), lastName(""), employeeNumber(-1), salary(DefaultStartingSalary), hired(false)
   {
   }

   void Employee::promote(int aRaiseAmount)
   {
      setSalary(getSalary() + aRaiseAmount);
   }

   void Employee::demote(int aDemetricAmount)
   {
      setSalary(getSalary() - aDemetricAmount);
   }

   void Employee::hire()
   {
      hired = true;
   }

   void Employee::fire()
   {
      hired = false;
   }

   void Employee::display() const
   {      
      cout << "Employee: " << getLastName() << ", " << getFirstName() << endl;
      cout << "-------------------------" << endl;
      cout << (hired ? "Current Employee" : "Former Employee") << endl;
      cout << "Employee Number: " << getEmployeeNumber() << endl;
      cout << "Salary: $" << getSalary() << endl;
      cout << endl;
   }

   void Employee::setFirstName(std::string aFirstName)
   {
      firstName = aFirstName;
   }

   string Employee::getFirstName() const
   {
      return firstName;
   }

   void Employee::setLastName(std::string aLastName)
   {
      lastName = aLastName;
   }

   string Employee::getLastName() const
   {
      return lastName;
   }

   void Employee::setEmployeeNumber(int anEmployeeNumber)
   {
      employeeNumber = anEmployeeNumber;
   }

   int Employee::getEmployeeNumber() const
   {
      return employeeNumber;
   }

   void Employee::setSalary(int aNewSalary)
   {
      salary = aNewSalary;
   }

   int Employee::getSalary() const
   {
      return salary;
   }

   bool Employee::getIsHired() const
   {
      return hired;
   }
}

