/**
 * Some C++ arithmetic
 */

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
   using namespace std;

   float hats, heads;

   cout.setf(ios_base::fixed, ios_base::floatfield); // fixed-point
   cout << "Enter a number: ";
   cin >> hats;
   cout << "Enter another number: ";
   cin >> heads;

   cout << "hats = " << hats << "; heads = " << heads << endl;
   cout << "hats + heads = " << hats + heads << endl;
   cout << "hats - heads = " << hats - heads << endl;
   cout << "hats * heads = " << hats * heads << endl;
   cout << "hats / heads = " << hats / heads << endl;

   return EXIT_SUCCESS;
}
