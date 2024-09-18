#include <iostream>
#include "Database.hpp"

using namespace std;
using namespace HR;

int displayMenu();

void doHire(Database &empDb);

void doFire(Database &empDb);

void doPromote(Database &empDb);

EmpType getEmpType(const char &empTypeSym);

int main()
{
   Database employeeDb;

   bool done{false};
   while (!done)
   {
      int selection{displayMenu()};
      switch (selection)
      {
         case 0:
            done = true;
            break;
         case 1:
            doHire(employeeDb);
            break;
         case 2:
            doFire(employeeDb);
            break;
         case 3:
            doPromote(employeeDb);
            break;
         case 4:
            employeeDb.displayAll();
            break;
         case 5:
            employeeDb.displayCurrent();
            break;
         case 6:
            employeeDb.displayFormer();
            break;
         default:
            std::cerr << std::format("Unknown command.");
            break;
      }
   }
}

int displayMenu()
{
   // Note:
   //		One important note is that this code assumes that the user will
   //		"play nice" and type a number when a number is requested.
   //		When you read about I/O in Chapter 13, you will learn how to
   //		protect against bad input.

   int selection;
   cout << format("") << endl;
   cout << format("Employee Database") << endl;
   cout << format("-----------------") << endl;
   cout << format("1) Hire a new employee") << endl;
   cout << format("2) Fire an employee") << endl;
   cout << format("3) Promote an employee") << endl;
   cout << format("4) List all employees") << endl;
   cout << format("5) List all current employees") << endl;
   cout << format("6) List all former employees") << endl;
   cout << format("0) Quit") << endl;
   cout << format("") << endl;
   cout << format("---> ");

   cin >> selection;

   return selection;
}

void doHire(Database &empDb)
{
   string firstName;
   string lastName;
   char empTypeSym;
   EmpType empType;

   cout << std::format("First name? ");
   cin >> firstName;

   cout << std::format("Last name? ");
   cin >> lastName;

   cout << std::format("Employee type? (E, S or M) ");
   cin >> empTypeSym;

   empType = getEmpType(empTypeSym);

   auto &employee{empDb.addEmployee(firstName, lastName, empType)};
   cout << format("Hired employee {} {} with employee number {}.",
                  firstName,
                  lastName,
                  employee.getEmployeeNumber()) << std::endl;
}

EmpType getEmpType(const char &empTypeSym)
{
   EmpType empType;
   switch (empTypeSym)
   {
      case 'E':
         empType = EmpType::Engineer;
         break;
      case 'S':
         empType = EmpType::Senior;
         break;
      case 'M':
         empType = EmpType::Manager;
         break;
      default:
         empType = EmpType::Engineer;
         break;
   }

   return empType;
}

void doFire(Database &empDb)
{
   int employeeNumber;
   cout << format("Employee number? ");
   cin >> employeeNumber;

   try
   {
      auto &emp{empDb.getEmployee(employeeNumber)};
      emp.fire();
      cout << format("Employee {} terminated.", employeeNumber) << endl;
   }
   catch (const logic_error &exception)
   {
      cerr << format("Unable to terminate employee: {}", exception.what()) << endl;
   }
}

void doPromote(Database &empDb)
{
   int employeeNumber;
   cout << format("Employee number? ");
   cin >> employeeNumber;

   int raiseAmount;
   cout << format("How much of a raise? ");
   cin >> raiseAmount;

   try
   {
      auto &emp{empDb.getEmployee(employeeNumber)};
      emp.promote(raiseAmount);
   }
   catch (const logic_error &exception)
   {
      cerr << format("Unable to promote employee: {}", exception.what()) << endl;
   }
}
