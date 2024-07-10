#include <iostream>
#include "Database.hpp"

using namespace std;
using namespace Records;

int displayMenu();

void doHire(Database &db);

void doFire(Database &db);

void doPromote(Database &db);

int main()
{
   Database employeeDB;

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
            doHire(employeeDB);
            break;
         case 2:
            doFire(employeeDB);
            break;
         case 3:
            doPromote(employeeDB);
            break;
         case 4:
            employeeDB.displayAll();
            break;
         case 5:
            employeeDB.displayCurrent();
            break;
         case 6:
            employeeDB.displayFormer();
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
   std::cout << std::format("") << std::endl;
   std::cout << std::format("Employee Database") << std::endl;
   std::cout << std::format("-----------------") << std::endl;
   std::cout << std::format("1) Hire a new employee") << std::endl;
   std::cout << std::format("2) Fire an employee") << std::endl;
   std::cout << std::format("3) Promote an employee") << std::endl;
   std::cout << std::format("4) List all employees") << std::endl;
   std::cout << std::format("5) List all current employees") << std::endl;
   std::cout << std::format("6) List all former employees") << std::endl;
   std::cout << std::format("0) Quit") << std::endl;
   std::cout << std::format("") << std::endl;
   std::cout << std::format("---> ");

   cin >> selection;

   return selection;
}

void doHire(Database &db)
{
   string firstName;
   string lastName;
   std::cout << std::format("First name? ");
   cin >> firstName;

   std::cout << std::format("Last name? ");
   cin >> lastName;

   auto &employee{db.addEmployee(firstName, lastName)};
   std::cout << std::format("Hired employee {} {} with employee number {}.",
                            firstName,
                            lastName,
                            employee.getEmployeeNumber()) << std::endl;
}

void doFire(Database &db)
{
   int employeeNumber;
   std::cout << std::format("Employee number? ");
   cin >> employeeNumber;

   try
   {
      auto &emp{db.getEmployee(employeeNumber)};
      emp.fire();
      std::cout << std::format("Employee {} terminated.", employeeNumber) << std::endl;
   }
   catch (const std::logic_error &exception)
   {
      std::cerr << std::format("Unable to terminate employee: {}", exception.what()) << std::endl;
   }
}

void doPromote(Database &db)
{
   int employeeNumber;
   std::cout << std::format("Employee number? ");
   cin >> employeeNumber;

   int raiseAmount;
   std::cout << std::format("How much of a raise? ");
   cin >> raiseAmount;

   try
   {
      auto &emp{db.getEmployee(employeeNumber)};
      emp.promote(raiseAmount);
   }
   catch (const std::logic_error &exception)
   {
      std::cerr << std::format("Unable to promote employee: {}", exception.what()) << std::endl;
   }
}

/*
void dbTest()
{
   Database myDB;

   Employee &emp1{myDB.addEmployee("Greg", "Wallis")};
   emp1.fire();

   Employee &emp2{myDB.addEmployee("Marc", "White")};
   emp2.setSalary(100'000);

   Employee &emp3{myDB.addEmployee("John", "Doe")};
   emp3.setSalary(10'000);
   emp3.promote();

   std::cout << std::format("All employees:\n==============") << std::endl;
   myDB.displayAll();

   std::cout << std::format("\nCurrent employees:\n==================") << std::endl;
   myDB.displayCurrent();

   std::cout << std::format("\nFormer employees:\n=================") << std::endl;
   myDB.displayFormer();
}

void empTest()
{
   std::cout << std::format("Testing the Employee class.") << std::endl;

   Employee emp{"Jane", "Doe"};
   emp.setFirstName("John");
   emp.setLastName("Doe");
   emp.setEmployeeNumber(71);
   emp.setSalary(50'000);
   emp.promote();
   emp.promote(50);
   emp.hire();
   emp.display();
}
 */