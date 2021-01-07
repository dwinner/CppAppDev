/**
 * rvalue references and move semantics
 */

#include <iostream>
#include "Useless.h"

int main()
{
   using std::cout;
   {
      Useless one(10, 'x');
      Useless two = one + one;   // calls move constructor
      cout << "object one: ";
      one.ShowData();
      cout << "object two: ";
      two.ShowData();
      Useless three, four;
      cout << "three = one\n";
      three = one;              // automatic copy assignment
      cout << "now object three = ";
      three.ShowData();
      cout << "and object one = ";
      one.ShowData();
      cout << "four = one + two\n";
      four = one + two;         // automatic move assignment
      cout << "now object four = ";
      four.ShowData();
      cout << "four = move(one)\n";
      four = std::move(one);    // forced move assignment
      cout << "now object four = ";
      four.ShowData();
      cout << "and object one = ";
      one.ShowData();
   }

   return 0;
}
