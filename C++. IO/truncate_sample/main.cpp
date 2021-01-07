/**
 * Using get() to truncate input line, if necessary
 */

#include <iostream>

const int slen = 10;

inline void eatLine()
{
   while (std::cin.get() != '\n')
   {
      continue;
   }
}

int main()
{
   using std::cin;
   using std::cout;
   using std::endl;

   char name[slen];
   char title[slen];
   cout << "Enter your name: ";
   cin.get(name, slen);
   if (cin.peek() != '\n')
   {
      cout << "Sorry, we only have enough room for "
           << name << endl;
   }

   eatLine();
   cout << "Dear " << name << ", enter your title: \n";
   cin.get(title, slen);
   if (cin.peek() != '\n')
   {
      cout << "We were forced to truncate your title.\n";
   }

   eatLine();
   cout << " Name: " << name
        << "\nTitle: " << title << endl;

   return 0;
}
