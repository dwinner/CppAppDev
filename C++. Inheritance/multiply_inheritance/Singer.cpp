#include <iostream>
#include "Singer.h"

using namespace std;

char* Singer::voiceTypes_[vtypes] =
{
   "other",
   "alto",
   "contralto",
   "soprano",
   "bass",
   "baritone",
   "tenor"
};

void Singer::set()
{
   cout << "Enter singer's name: ";
   Worker::get();
   get();
}

void Singer::show() const
{
   cout << "Category: singer\n";
   Worker::data();
   data();
}

// protected methods
void Singer::data() const
{
   cout << "Vocal range: " << voiceTypes_[voice_] << endl;
}

void Singer::get()
{
   cout << "Enter number for singer's vocal range:\n";
   int i;
   for (i = 0; i < vtypes; i++)
   {
      cout << i << ": " << voiceTypes_[i] << "   ";
      if (i % 4 == 3)
      {
         cout << endl;
      }
   }

   if (i % 4 != 0)
   {
      cout << '\n';
   }

   while (cin >> voice_ && (voice_ < 0 || voice_ >= vtypes))
   {
      cout << "Please enter a value >= 0 and < " << vtypes << endl;
   }

   while (cin.get() != '\n')
   {
   }
}
