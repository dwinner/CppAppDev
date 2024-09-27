#include <iostream>
#include <array>
#include <vector>
#include <format>
#include <algorithm>
#include "Person.hpp"

static constexpr const auto empLen = 4;

using namespace std;
using namespace HR;

void cmp_check();

int main()
{
   cmp_check();

   return 0;
}

void cmp_check()
{
   vector<Person> employees;
   employees.emplace_back("John", "Doe");
   employees.emplace_back("Foo", "Bar");
   employees.emplace_back("James", "Bond");
   employees.emplace_back("Anna", "Boo");
   employees.emplace_back("Beetle", "Jose");
   employees.emplace_back("Sweeney", "Todd");

   // print unsorted
   for (const auto &item: employees)
   {
      cout << item << endl;
   }

   cout << endl << endl;

   std::sort(employees.begin(), employees.end());

   // print sorted
   for (const auto &item: employees)
   {
      cout << item << endl;
   }
}
