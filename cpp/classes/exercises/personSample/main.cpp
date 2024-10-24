#include <iostream>
#include <array>
#include "Person.hpp"

static constexpr const auto empLen = 3;
using namespace std;

int main()
{
   Person person1{"Sata", "Jones"};
   cout << person1 << endl;

   auto person2 = make_unique<Person>("Holy", "Water");
   cout << *person2 << endl;

   array<Person, empLen> employees;
   for (auto &employee : employees)
   {
      employee = person1;
   }

   employees[0].setFirstName("Den");
   employees[0].setLastName("Win");

   for (const auto &person: employees)
   {
      cout << person << endl;
   }

   return 0;
}
