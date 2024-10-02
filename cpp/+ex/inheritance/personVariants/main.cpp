#include <iostream>
#include <vector>
#include <memory>
#include "Person.hpp"
#include "Employee.hpp"
#include "Manager.hpp"
#include "Director.hpp"

using namespace std;
using namespace HR;

int main()
{
   vector<unique_ptr<Person>> employees;

   employees.push_back(make_unique<Person>("John", "Doe"));
   employees.push_back(make_unique<Employee>("Foo", "Bar", 1));
   employees.push_back(make_unique<Employee>("James", "Bond", 2));
   employees.push_back(make_unique<Employee>("Anna", "Boo", 3));
   employees.push_back(make_unique<Manager>("Beetle", "Jose", 4));
   employees.push_back(make_unique<Director>("Sweeney", "Todd", 5));

   for (const auto &item: employees)
   {
      cout << *item << endl;
   }

   return 0;
}
