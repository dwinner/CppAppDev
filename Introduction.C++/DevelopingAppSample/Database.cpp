#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include "Database.h"

using namespace std;

namespace Records
{
   Database::Database()
   {
      nextEmployeeNumber = FirstEmployeeNumber;
   }

   Database::~Database()
   {
   }

   Employee& Database::addEmployee(string aFirstName, string aLastName)
   {
      Employee theEmployee;
      theEmployee.setFirstName(aFirstName);
      theEmployee.setLastName(aLastName);
      theEmployee.setEmployeeNumber(nextEmployeeNumber++);
      theEmployee.hire();
      employees.push_back(theEmployee);

      return employees[employees.size() - 1];
   }

   Employee& Database::getEmployee(int anEmployeeNumber)
   {
      for (auto iter = employees.begin(); iter != employees.end(); ++iter)
      {
         if (iter->getEmployeeNumber() == anEmployeeNumber)
         {
            return *iter;
         }
      }

      cerr << "No employee with employee number " << anEmployeeNumber << endl;
      throw exception();
   }

   Employee& Database::getEmployee(string aFirstName, string aLastName)
   {
      for (auto iter = employees.begin(); iter != employees.end(); ++iter)
      {
         if (iter->getFirstName() == aFirstName && iter->getLastName() == aLastName)
         {
            return *iter;
         }
      }

      cerr << "No match with name " << aFirstName << " " << aLastName << endl;
      throw exception();
   }

   void Database::displayAll() const
   {
      for (auto iter = employees.begin(); iter != employees.end(); ++iter)
      {
         iter->display();
      }
   }

   void Database::displayCurrent() const
   {
      for (auto iter = employees.begin(); iter != employees.end(); ++iter)
      {
         iter->display();
      }
   }

   void Database::displayFormer() const
   {
      for (auto iter = employees.begin(); iter != employees.end(); ++iter)
      {
         if (!iter->getIsHired())
         {
            iter->display();
         }
      }
   }
}

