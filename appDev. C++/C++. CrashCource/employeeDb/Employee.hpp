#pragma once

#include <string>
#include <ostream>
#include <format>
#include <iostream>

namespace Records
{
   class Employee
   {
   public:
      Employee(std::string firstName, std::string lastName);

      void promote(int raiseAmount = DefaultRaiseAndDemeritAmount);

      [[maybe_unused]] void demote(int demeritAmount = DefaultRaiseAndDemeritAmount);

      /**
       * @brief Hires or rehires the employee
       */
      void hire();

      /**
       * @brief Dismisses the employee
       */
      void fire();

      /**
       * @brief Prints employee info
       */
      void display() const;

      [[nodiscard]] const std::string &getFirstName() const;

      [[maybe_unused]] void setFirstName(const std::string &firstName);

      [[nodiscard]] const std::string &getLastName() const;

      [[maybe_unused]] void setLastName(const std::string &lastName);

      [[nodiscard]] int getEmployeeNumber() const;

      void setEmployeeNumber(int employeeNumber);

      [[nodiscard]] int getSalary() const;

      void setSalary(int newSalary);

      [[nodiscard]] bool isHired() const;

   private:
      static const int DefaultStartingSalary{30'000};
      static const int DefaultRaiseAndDemeritAmount{1'000};

      std::string _firstName;
      std::string _lastName;
      int _employeeNumber{-1};
      int _salary{DefaultStartingSalary};
      bool _hired{false};
   };
}
