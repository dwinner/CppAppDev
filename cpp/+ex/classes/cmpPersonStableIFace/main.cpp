#include <iostream>
#include <vector>
#include <algorithm>
#include "Person.hpp"

using namespace std;
using namespace hr;

void Cmp_check();

int main()
{
   Cmp_check();

   return 0;
}

void Cmp_check()
{
   vector<Person> employees;
   employees.emplace_back("John", "Doe");
   employees.emplace_back("Foo", "Bar");
   employees.emplace_back("James", "Dean");
   employees.emplace_back("Anna", "Boo");
   employees.emplace_back("Beetle", "Jose");
   employees.emplace_back("Sweeney", "Todd");

   // print unsorted
   for (const auto& item : employees)
   {
      cout << item << '\n';
   }

   cout << '\n' << '\n';

   ranges::sort(employees);

   // print sorted
   for (const auto& item : employees)
   {
      cout << item << '\n';
   }
}
