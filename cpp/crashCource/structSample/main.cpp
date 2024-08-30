#include <iostream>
#include <format>
#include "employee.hpp"

using namespace std;

int main()
{
   // create and populate an employee
   Employee anEmployee{};
   anEmployee.firstInitial = 'J';
   anEmployee.lastInitial = 'D';
   anEmployee.employeeNumber = 42;
   anEmployee.salary = 80000;

   // output the values of an employee
   cout << std::format("Employee: {}{}", anEmployee.firstInitial, anEmployee.lastInitial) << endl;
   cout << std::format("Number: {}", anEmployee.employeeNumber) << endl;
   cout << std::format("Salary: ${}", anEmployee.salary) << endl;

   return 0;
}
