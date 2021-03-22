/**
 * Input and output
 */

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
   using namespace std;

   int carrots;

   cout << "How many carrots do you have?" << endl;
   cin >> carrots;
   cout << "Here are two more. ";
   carrots = carrots + 2;
   cout << "Now you have " << carrots << " carrots." << endl;

   return EXIT_SUCCESS;
}
