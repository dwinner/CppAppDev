#include <atomic>
#include <iostream>

using namespace std;

long mulWith(volatile atomic_long *alPtr, long val)    // *=
{
   long old = *alPtr, newVal;

   do
   {
      newVal = old * val;
   }
   while (!atomic_compare_exchange_weak(alPtr, &old, newVal));

   return newVal;
}

int main()
{
   atomic_long a_value = 12L;
   mulWith(&a_value, 5L);
   std::cout << "12 * 5 = " << a_value;

   return 0;
}
