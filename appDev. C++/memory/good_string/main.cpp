#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GoodString.h"

const int ArSize = 10;
const int MaxLen = 81;

void using1();

void using2();

int main()
{
   using1();
   using2();

   return 0;
}

void using2()
{
   using namespace std;
   GoodString name;
   cout << "Hi, what's your name?\n>> ";
   cin >> name;

   cout << name << ", please enter up to " << ArSize << " short sayings <empty line to quit>:\n";
   GoodString sayings[ArSize];
   char temp[MaxLen]; // temporary string storage
   int i;
   for (i = 0; i < ArSize; i++)
   {
      cout << i + 1 << ": ";
      cin.get(temp, MaxLen);
      while (cin && cin.get() != '\n')
      {
      }

      if (!cin || temp[0] == '\0') // empty line?
      {
         break; // i not incremented
      }

      sayings[i] = temp; // overloaded assignment
   }

   int total = i; // total # of lines read

   if (total > 0)
   {
      cout << "Here are your sayings:\n";
      for (i = 0; i < total; i++)
      {
         cout << sayings[i] << "\n";
      }

      // use pointers to keep track of shortest, first strings
      GoodString* shortest = &sayings[0]; // initialize to first object
      GoodString* first = &sayings[0];
      for (i = 1; i < total; i++)
      {
         if (sayings[i].length() < shortest->length())
         {
            shortest = &sayings[i];
         }

         if (sayings[i] < *first) // compare values
         {
            first = &sayings[i]; // assign address
         }
      }

      cout << "Shortest saying:\n" << *shortest << endl;
      cout << "First alphabetically:\n" << *first << endl;

      srand(time(nullptr));
      int choice = rand() % total; // pick index at random

      // use new to create, initialize new String object
      const auto* const favorite = new GoodString(sayings[choice]);
      cout << "My favorite saying:\n" << *favorite << endl;

      delete favorite;
   }
   else
   {
      cout << "Not much to say, eh?\n";
   }

   cout << "Bye.\n";
}

void using1()
{
   using std::cout;
   using std::cin;
   using std::endl;
   GoodString name;
   cout << "Hi, what's your name?\n>> ";
   cin >> name;

   cout << name << ", please enter up to " << ArSize
      << " short sayings <empty line to quit>:\n";
   GoodString sayings[ArSize]; // array of objects
   char temp[MaxLen]; // temporary string storage
   int i;
   for (i = 0; i < ArSize; i++)
   {
      cout << i + 1 << ": ";
      cin.get(temp, MaxLen);
      while (cin && cin.get() != '\n')
         continue;
      if (!cin || temp[0] == '\0') // empty line?
         break; // i not incremented
      sayings[i] = temp;
      // overloaded assignment
   }
   int total = i; // total # of lines read

   if (total > 0)
   {
      cout << "Here are your sayings:\n";
      for (i = 0; i < total; i++)
         cout << sayings[i][0] << ": " << sayings[i] << endl;

      int shortest = 0;
      int first = 0;
      for (i = 1; i < total; i++)
      {
         if (sayings[i].length() < sayings[shortest].length())
            shortest = i;
         if (sayings[i] < sayings[first])
            first = i;
      }
      cout << "Shortest saying:\n" << sayings[shortest] << endl;
      cout << "First alphabetically:\n" << sayings[first] << endl;
      cout << "This program used " << GoodString::howMany()
         << " String objects. Bye.\n";
   }
   else
      cout << "No input! Bye.\n";
}
