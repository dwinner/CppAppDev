/**
 * Uses and displays a variable
 */

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
   using namespace std;

   int carrots;

   carrots = 25;
   cout << "I have ";
   cout << carrots;
   cout << " carrots. ";
   cout << endl;
   carrots = carrots - 1;
   cout << "Crunch, crunch. Now I have " << carrots << " carrots" << endl;

   return EXIT_SUCCESS;
}
