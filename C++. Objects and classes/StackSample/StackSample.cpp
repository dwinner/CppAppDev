#include <iostream>
#include <cctype>
#include "Stack.h"

int main()
{
   using namespace std;
   using namespace stacksample;

   Stack stack; // create an empty stack
   char ch;
   unsigned long po;
   cout << "Please enter A to add a purchase order,\n P to process a PO, or Q to quit.\n";

   while (cin >> ch && toupper(ch) != 'Q')
   {
      while (cin.get() != '\n')
      {
      }

      if (!isalpha(ch))
      {
         cout << '\a';
         continue;
      }

      switch (ch)
      {
      case 'A':
      case 'a':
         cout << "Enter a PO number to add: ";
         cin >> po;
         if (stack.is_full())
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
         if (stack.is_empty())
         {
            cout << "stack already empty\n";
         }
         else
         {
            stack.pop(po);
            cout << "PO #" << po << " popped\n";
         }
         break;
      default:
         break;
      }

      cout << "Please enter A to add a purchase order,\n P to process a PO, or Q to quit.\n";
   }

   cout << "Bye\n";

   return 0;
}
