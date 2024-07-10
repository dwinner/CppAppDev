#include <iostream>

namespace myCode
{
   void foo()
   {
      std::printf("foo() called in the myCode namespace\"\n");
   }
}


using namespace myCode;

int main()
{
   myCode::foo();
   foo();

   return 0;
}
