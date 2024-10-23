#pragma once

#include <string>

namespace records
{
   const int DefaultStartingSalary{30'000};
   const int DefaultRaiseAndDemeritAmount{1'000};

   class Employee
   {
   public:
      Employee(const std::string &firstName, const std::string &lastName);

      void promote(int raiseAmount = DefaultRaiseAndDemeritAmount);

      void demote(int demeritAmount = DefaultRaiseAndDemeritAmount);

      void hire(); // Hires or rehires the employee

      void fire(); // Dismisses the employee

      void display() const;// Outputs employee info to console

      // Getters and setters

      void setFirstName(const std::string &firstName);

      const std::string &getFirstName() const;

      void setLastName(const std::string &lastName);

      const std::string &getLastName() const;

      void setEmployeeNumber(int employeeNumber);

      int getEmployeeNumber() const;

      void setSalary(int newSalary);

      int getSalary() const;

      bool isHired() const;

   private:
      std::string firstName_;
      std::string lastName_;
      int employeeNumber_{-1};
      int salary_{DefaultStartingSalary};
      bool hired_{false};
   };
}
