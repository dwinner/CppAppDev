#pragma once

namespace Records
{
   const int DefaultStartingSalary = 30000;

   class Employee
   {
   public:
      Employee();

      void promote(int aRaiseAmount = 1000);
      void demote(int aDemetricAmount = 1000);
      void hire();
      void fire();
      void display() const;

      void setFirstName(std::string aFirstName);
      std::string getFirstName() const;
      void setLastName(std::string aLastName);
      std::string getLastName() const;
      void setEmployeeNumber(int anEmployeeNumber);
      int getEmployeeNumber() const;
      void setSalary(int aNewSalary);
      int getSalary() const;
      bool getIsHired() const;

   protected:
      std::string firstName;
      std::string lastName;
      int employeeNumber;
      int salary;
      bool hired;
   };
}

