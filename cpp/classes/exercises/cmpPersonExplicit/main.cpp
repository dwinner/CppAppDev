#include <iostream>
#include <array>
#include <vector>
#include <format>
#include <algorithm>
#include "Person.hpp"

static constexpr const auto empLen = 4;

using namespace std;
using namespace HR;

Person create_person();

void move_op_check();

void cmp_check();

int main()
{
   cmp_check();

   return 0;
}

Person create_person()
{
   return Person{"Random name", "Random surname"};
}

void move_op_check()
{
   vector<Person> staff;
   for (size_t i{0}; i < empLen; ++i)
   {
      cout << format("Iteration {}", i) << endl;
      string firstName = format("first-{}", i);
      string lastName = format("last-{}", i);
      staff.emplace_back(firstName, lastName);
      cout << format("") << endl;
   }

   Person person1{"Mark", "Gregory"};
   person1 = create_person();

   cout << person1 << endl;
   cout << format("") << endl;

   Person person2{"Gerbert", "Shildtt"};
   person2 = std::move(person1);

   cout << person2 << endl;
   cout << format("") << endl;

   person2.setFirstName("Den");
   person2.setLastName("Win");
   person2.setInitials("DW");

   cout << person2 << endl;
   cout << format("") << endl;

   swap(person1, person2);
   cout << person1 << endl;
   cout << person2 << endl;
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
