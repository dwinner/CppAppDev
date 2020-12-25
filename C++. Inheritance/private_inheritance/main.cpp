/**
 * Private inheritance sample
 */

#include <iostream>
#include "Student.h"

using std::cin;
using std::cout;
using std::endl;

void set(Student& student, int studentCount);

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
   for (i = 0; i < Pupils; i++)
   {
      set(ada[i], Quizzes);
   }

   cout << "\nStudent List:\n";
   for (i = 0; i < Pupils; ++i)
   {
      cout << ada[i].getStudentName() << endl;
   }

   cout << "\nResults:";
   for (i = 0; i < Pupils; i++)
   {
      cout << endl << ada[i];
      cout << "average: " << ada[i].average() << endl;
   }

   cout << "Done.\n";

   return 0;
}

void set(Student& student, int studentCount)
{
   cout << "Please enter the student's name: ";
   getline(cin, student);
   cout << "Please enter " << studentCount << " quiz scores:\n";
   for (int i = 0; i < studentCount; i++)
   {
      cin >> student[i];
   }

   while (cin.get() != '\n')
   {
   }
}
