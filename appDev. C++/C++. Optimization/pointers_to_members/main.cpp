/**
 * Dereferencing pointers to class members
 */

#include <iostream>
#include "Example.h"

using namespace std;

int main()
{
   Example car(15);
   Example van(20);
   Example garage;

   cout << "car.use_ptr() output:\n";
   car.use_ptr();
   cout << "\nvan.use_ptr() output:\n";
   van.use_ptr();
   cin.get();

   return 0;
}