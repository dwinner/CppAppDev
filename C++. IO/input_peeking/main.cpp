/**
 * Some istream methods
 */

#include <iostream>

int main()
{
   using std::cout;
   using std::cin;
   using std::endl;

   //  read and echo input up to a # character
   char character;

   while (cin.get(character))          // terminates on EOF
   {
      if (character != '#')
      {
         cout << character;
      }
      else
      {
         cin.putback(character);    // reinsert character
         break;
      }
   }

   if (!cin.eof())
   {
      cin.get(character);
      cout << endl << character << " is next input character.\n";
   }
   else
   {
      cout << "End of file reached.\n";
      std::exit(EXIT_SUCCESS);
   }

   while (cin.peek() != '#')    // look ahead
   {
      cin.get(character);
      cout << character;
   }

   if (!cin.eof())
   {
      cin.get(character);
      cout << endl << character << " is next input character.\n";
   }
   else
   {
      cout << "End of file reached.\n";
   }

   // keeping output window open

   return 0;
}
