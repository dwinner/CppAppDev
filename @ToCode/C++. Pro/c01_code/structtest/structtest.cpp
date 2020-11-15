#include <iostream>
#include "employeestruct.h"

using namespace std;

int main()
{
	// create and populate an employee
	Employee anEmployee;

	anEmployee.firstInitial = 'M';
	anEmployee.lastInitial = 'G';
	anEmployee.employeeNumber = 42;
	anEmployee.salary = 80000;

	// output the values of an employee
	cout << "Employee: " << anEmployee.firstInitial << 
							anEmployee.lastInitial << endl;
	cout << "Number: " << anEmployee.employeeNumber << endl;
	cout << "Salary: $" << anEmployee.salary << endl;

	return 0;
}
