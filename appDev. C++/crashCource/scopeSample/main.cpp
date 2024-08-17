#include <iostream>
#include <format>

using namespace std;

class Demo
{
public:
   int get()
   { return 5; }
};

int get()
{ return 10; }

namespace NS
{
   int get()
   { return 20; }
}

int main()
{
   Demo d;
   cout << std::format("{}", d.get()) << endl;      // prints 5
   cout << std::format("{}", NS::get()) << endl;    // prints 20
   cout << std::format("{}", ::get()) << endl;      // prints 10
   cout << std::format("{}", get()) << endl;        // prints 10

   return 0;
}
