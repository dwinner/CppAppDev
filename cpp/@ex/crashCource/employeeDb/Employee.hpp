#pragma once

#include <string>
#include <ostream>
#include <format>
#include <iostream>
#include "EmpType.hpp"

namespace HR
{
   class Employee
   {
   public:
      Employee(std::string firstName, std::string lastName, EmpType empType = EmpType::Engineer);

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

      [[nodiscard]] EmpType getEmpType() const;

      void setEmpType(EmpType empType);

   private:
      static const int DefaultStartingSalary{30'000};
      static const int DefaultRaiseAndDemeritAmount{1'000};

      [[nodiscard]] std::string empTypeAsString() const;

      std::string _firstName;
      std::string _lastName;
      EmpType _empType;
      int _employeeNumber{-1};
      int _salary{DefaultStartingSalary};
      bool _hired{false};
   };
}
