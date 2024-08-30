#include "Student.h"

using std::ostream;
using std::endl;
using std::istream;
using std::string;

double Student::average() const
{
   return ArrayDb::size() > 0
             ? sum() / ArrayDb::size()
             : 0;
}

const string& Student::getStudentName() const
{
   return static_cast<const string&>(*this);
}

double& Student::operator[](int index)
{
   return ArrayDb::operator[](index); // use ArrayDb::operator[]()
}

double Student::operator[](int index) const
{
   return ArrayDb::operator[](index);
}

// private method
ostream& Student::arr_out(ostream& outputStream) const
{
   int i;
   int lim = ArrayDb::size();
   if (lim > 0)
   {
      for (i = 0; i < lim; i++)
      {
         outputStream << ArrayDb::operator[](i) << " ";
         if (i % 5 == 4)
         {
            outputStream << endl;
         }
      }

      if (i % 5 != 0)
      {
         outputStream << endl;
      }
   }
   else
   {
      outputStream << " empty array ";
   }

   return outputStream;
}

// friends
// use String version of operator>>()
istream& operator>>(istream& inputStream, Student& student)
{
   inputStream >> static_cast<string&>(student);
   return inputStream;
}

// use string friend getline(ostream &, const string &)
istream& getline(istream& inputStream, Student& student)
{
   getline(inputStream, static_cast<string&>(student));
   return inputStream;
}

// use string version of operator<<()
ostream& operator<<(ostream& outputStream, const Student& student)
{
   outputStream << "Scores for " << static_cast<const string&>(student) << ":\n";
   student.arr_out(outputStream); // use private method for scores
   return outputStream;
}
