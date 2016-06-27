// DevelopingAppSample.cpp: Небольшое приложение для демонстрации первичных принципов разработки на C++.

#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include "Database.h"
#include <string>;

using namespace std;
using namespace Records;

int displayMenu();
void doHire(Database& inDb);
void doFire(Database& inDb);
void doPromote(Database& inDb);

int main()
{
   Database employeeDb;
   bool done = false;

   while (!done)
   {
      int selection = displayMenu();

      switch (selection)
      {
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
            cerr << "Unknown command." << endl;
            done = true;
            break;
      }
   }

   return 0;
}

void doHire(Database& inDb)
{
   string firstName;
   string lastName;

   cout << "First name? ";
   cin >> firstName;
   cout << "Last name? ";
   cin >> lastName;

   try
   {
      inDb.addEmployee(firstName, lastName);
   }
   catch (const exception&)
   {
      cerr << "Unable to add new employee!" << endl;
   }
}

void doFire(Database& inDb)
{
   int employeeNumber;

   cout << "Employee number? ";
   cin >> employeeNumber;

   try
   {
      Employee& emp = inDb.getEmployee(employeeNumber);
      emp.fire();
      cout << "Employee " << employeeNumber << " has been terminated." << endl;
   }
   catch (const exception&)
   {
      cerr << "Unable to terminate employee!" << endl;
   }
}

void doPromote(Database& inDb)
{
   int employeeNumber;
   int raiseAmount;

   cout << "Employee number? ";
   cin >> employeeNumber;

   cout << "How much of a raise? ";
   cin >> raiseAmount;

   try
   {
      Employee& emp = inDb.getEmployee(employeeNumber);
      emp.promote(raiseAmount);
   }
   catch (const exception&)
   {
      cerr << "Unable to promote employee!" << endl;
   }
}

int displayMenu()
{
   int selection;

   cout << endl;
   cout << "Employee Database" << endl;
   cout << "-----------------" << endl;
   cout << "1) Hire a new employee" << endl;
   cout << "2) Fire an employee" << endl;
   cout << "3) Promote an employee" << endl;
   cout << "4) List all employees" << endl;
   cout << "5) List all current employees" << endl;
   cout << "6) List all previous employees" << endl;
   cout << "0) Quit" << endl;
   cout << endl;
   cout << "---> ";

   cin >> selection;

   return selection;
}

