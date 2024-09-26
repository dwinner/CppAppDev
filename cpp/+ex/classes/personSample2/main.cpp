#include <iostream>
#include <array>
#include <vector>
#include <format>
#include "Person.hpp"

static constexpr const auto empLen = 4;

using namespace std;
using namespace HR;

Person create()
{
   return Person{"Random name", "Random surname"};
}

int main()
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
   person1 = create();

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

   HR::swap(person1, person2);
   cout << person1 << endl;
   cout << person2 << endl;

   return 0;
}
