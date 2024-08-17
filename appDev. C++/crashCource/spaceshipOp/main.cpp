#include <iostream>

void spaceShip1()
{
   using namespace std;

   int i{11};
   strong_ordering result{i <=> 0};
   if (result == strong_ordering::less)
   {
      cout << "less";
   }
   if (result == strong_ordering::greater)
   {
      cout << "greater";
   }
   if (result == strong_ordering::equal)
   {
      cout << "equal";
   }
}

void spaceShip2()
{
   using namespace std;

   int i{11};
   strong_ordering result{i <=> 0};
   if (is_lt(result))
   {
      cout << "less";
   }
   if (is_gt(result))
   {
      cout << "greater";
   }
   if (is_eq(result))
   {
      cout << "equal";
   }
}

int main()
{
   spaceShip1();
   spaceShip2();

   return 0;
}