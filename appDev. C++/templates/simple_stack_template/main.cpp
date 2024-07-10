/**
 * testing the template stack class
 */

#include <iostream>
#include <string>
#include <cctype>
#include "Stack.h"

using std::cin;
using std::cout;

int main()
{
   Stack<std::string> stack;   // create an empty stack
   char character;
   std::string po;
   cout << "Please enter A to add a purchase order,\n"
        << "P to process a PO, or Q to quit.\n";
   while (cin >> character && std::toupper(character) != 'Q')
   {
      while (cin.get() != '\n')
      {
      }

      if (!std::isalpha(character))
      {
         cout << '\a';
         continue;
      }

      switch (character)
      {
         case 'A':
         case 'a':
            cout << "Enter a PO number to add: ";
            cin >> po;
            if (stack.isFull())
            {
               cout << "stack already full\n";
            }
            else
            {
               stack.push(po);
            }
            break;
         case 'P':
         case 'p':
            if (stack.isEmpty())
            {
               cout << "stack already empty\n";
            }
            else
            {
               stack.pop(po);
               cout << "PO #" << po << " popped\n";
               break;
            }
      }

      cout << "Please enter A to add a purchase order,\n"
           << "P to process a PO, or Q to quit.\n";
   }

   cout << "Bye\n";

   return 0;
}