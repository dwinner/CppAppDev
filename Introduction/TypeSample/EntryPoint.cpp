// Типы данных

#include <iostream>

using namespace std;

int main()
{
   auto someInteger = 256;
   short someShrot;
   long someLong;
   float someFloat;
   double someDouble;

   someInteger++;
   someInteger *= 2;
   someShrot = short(someInteger);
   someLong = someShrot * 10000;
   someFloat = someLong + 0.785;
   someDouble = static_cast<double>(someFloat) / 100000;

   cout << someDouble << endl;
}

