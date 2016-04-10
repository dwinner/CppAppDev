// StructSample.cpp : Структуры.

#include "stdafx.h"
#include <iostream>
#include "EmployeeStruct.h"

using namespace std;

int main()
{
   EmployeeStruct anEmployee;

   anEmployee.firstInitial = 'M';
   anEmployee.middleInitial = 'R';
   anEmployee.lastInitial = 'G';
   anEmployee.employeeNumber = 42;
   anEmployee.salary = 80000;

   cout << "Employee: " << anEmployee.firstInitial << anEmployee.middleInitial << anEmployee.lastInitial << endl;
   cout << "Number: " << anEmployee.employeeNumber << endl;
   cout << "Salary: $" << anEmployee.salary << endl;

   return 0;
}

