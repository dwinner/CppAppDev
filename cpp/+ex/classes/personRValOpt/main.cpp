#include <iostream>
#include "Person.hpp"

using namespace std;

Person MakePerson()
{
   return Person{"First-1", "Last-1"};
}

int main()
{
   const Person person{"John", "Doe"};
   cout << format("{}", person.getFirstName()) << '\n';
   cout << format("{}", Person{"Foo", "Bar"}.getLastName()) << '\n';

   auto rVal{MakePerson()};
   rVal = Person{"First-1", "Last-1"};

   return 0;
}
