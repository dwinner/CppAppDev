/**
 * Converts stone to pounds
 */

#include <cstdlib>
#include <iostream>

int stone_to_lb(int);

int main(int argc, char* argv[])
{
   using namespace std;
   int stone;
   cout << "Enter the weight in stone: ";
   cin >> stone;
   const auto pounds = stone_to_lb(stone);
   cout << stone << " stone = ";
   cout << pounds << " pounds. " << endl;

   return EXIT_SUCCESS;
}

int stone_to_lb(const int sts)
{
   return 14 * sts;
}
