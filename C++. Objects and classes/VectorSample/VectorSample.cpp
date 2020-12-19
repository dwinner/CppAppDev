/**
 * Random walker emulation
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vector.h"

int main()
{
   using namespace std;
   // using namespace math_vector;
   using math_vector::Vector;

   srand(time(nullptr)); // seed random-number generator
   Vector step = Vector();
   Vector result(0.0, 0.0);
   unsigned long steps = 0;
   double target;
   double dstep;
   cout << "Enter target distance (q to quit): ";
   while (cin >> target)
   {
      cout << "Enter step length: ";
      if (!(cin >> dstep))
      {
         break;
      }

      double direction = .0;
      while (result.getMagnitude() < target)
      {
         direction = rand() % 360;
         step.reset(dstep, direction, Vector::polar_view);
         result = result + step;
         steps++;
      }

      cout << "After " << steps << " steps, the subject has the following location:\n";
      cout << result << endl;
      result.setMode(Vector::polar_view);
      cout << " or\n" << result << endl;
      cout << "Average outward distance per step = " << result.getMagnitude() / steps << endl;
      steps = 0;
      result.reset(0.0, 0.0);
      cout << "Enter target distance (q to quit): ";
   }

   cout << "Bye!\n";

   return 0;
}
