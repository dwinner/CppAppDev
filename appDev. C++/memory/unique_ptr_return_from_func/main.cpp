#include <iostream>
#include <memory>

using namespace std;

void println(const char *str)
{
   cout << str << endl;
}

class Simple
{
public:
   Simple()
   {
      println("Simple constructor called!");
   }

   ~Simple()
   {
      println("Simple destructor called!");
   }
};

unique_ptr<Simple> create()
{
   auto ptr{make_unique<Simple>()};
   // Do something with ptr...
   return ptr;
}

int main()
{
   unique_ptr<Simple> mySmartPtr1{create()};
   auto mySmartPtr2{create()};

   return 0;
}
