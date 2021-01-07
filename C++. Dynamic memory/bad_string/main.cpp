// vegnews.cpp -- using new and delete with classes
// compile with stringbad.cpp

#include <iostream>

using std::cout;

#include "BadString.h"

void callme1(BadString &);  // pass by reference
void callme2(BadString);    // pass by value

int main()
{
   using std::endl;
   {
      cout << "Starting an inner block.\n";
      BadString headline1("Celery Stalks at Midnight");
      BadString headline2("Lettuce Prey");
      BadString sports("Spinach Leaves Bowl for Dollars");
      cout << "headline1: " << headline1 << endl;
      cout << "headline2: " << headline2 << endl;
      cout << "sports: " << sports << endl;
      callme1(headline1);
      cout << "headline1: " << headline1 << endl;
      callme2(headline2);
      cout << "headline2: " << headline2 << endl;
      cout << "Initialize one object to another:\n";
      BadString sailor = sports;
      cout << "sailor: " << sailor << endl;
      cout << "Assign one object to another:\n";
      BadString knot;
      knot = headline1;
      cout << "knot: " << knot << endl;
      cout << "Exiting the block.\n";
   }

   cout << "End of main()\n";
   // std::cin.get();
   return 0;
}

void callme1(BadString &rsb)
{
   cout << "String passed by reference:\n";
   cout << "    \"" << rsb << "\"\n";
}

void callme2(BadString sb)
{
   cout << "String passed by value:\n";
   cout << "    \"" << sb << "\"\n";
}
