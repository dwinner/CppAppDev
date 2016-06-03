/**
 * Инициализаторы в конструкторах
 */

#include <iostream>
#include <stdexcept>
#include "PointSequence.h"

using namespace std;

int main()
{
   PointSequence p1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
   p1.dumpPoints();
   try
   {
      PointSequence p2 = {1.0, 2.0, 3.0};
   }
   catch (const invalid_argument &e)
   {
      cout << e.what() << endl;
   }

   return 0;
}