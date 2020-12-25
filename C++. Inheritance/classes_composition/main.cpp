/**
 * using composition for class
 */

#include <iostream>
#include "Student.h"

using std::cin;
using std::cout;
using std::endl;

void set(Student& aStudent, int studCount);

const int Pupils = 3;
const int Quizzes = 5;

int main()
{
   Student ada[Pupils] =
   {
      Student(Quizzes),
      Student(Quizzes),
      Student(Quizzes)
   };

   int i;
   for (i = 0; i < Pupils; ++i)
   {
      set(ada[i], Quizzes);
   }

   cout << "\nStudent List:\n";

   for (i = 0; i < Pupils; ++i)
   {
      cout << ada[i].getName() << endl;
   }

   cout << "\nResults:";

   for (i = 0; i < Pupils; ++i)
   {
      cout << endl << ada[i];
      cout << "average: " << ada[i].average() << endl;
   }

   cout << "Done.\n";

   return 0;
}

void set(Student& aStudent, int studCount)
{
   cout << "Please enter the student's name: ";
   getline(cin, aStudent);
   cout << "Please enter " << studCount << " quiz scores:\n";
   for (int i = 0; i < studCount; i++)
   {
      cin >> aStudent[i];
   }

   while (cin.get() != '\n')
   {
   }
}
