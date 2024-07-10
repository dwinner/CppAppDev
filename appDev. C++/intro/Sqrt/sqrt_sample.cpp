/**
 * Using the sqrt() function
 */

#include <cstdlib>
#include <iostream>
#include <cmath>

int main(int argc, char* argv[])
{
   using namespace std;

   double area;
   cout << "Enter the floor area, in square feet, of your home: ";
   cin >> area;

   double side;
   side = sqrt(area);
   cout << "That's the equivalent of a square " << side
      << " feet to the side." << endl;
   cout << "How fascinating!" << endl;

   return EXIT_SUCCESS;
}
