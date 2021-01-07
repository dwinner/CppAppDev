#include "Student.h"

using std::ostream;
using std::endl;
using std::istream;
using std::string;

double Student::average() const
{
   return scores_.size() > 0
             ? scores_.sum() / scores_.size()
             : 0;
}

const string& Student::getName() const
{
   return name_;
}

double& Student::operator[](int index)
{
   return scores_[index]; // use valarray<double>::operator[]()
}

double Student::operator[](int index) const
{
   return scores_[index];
}

// private method
ostream& Student::arr_out(ostream& oStream) const
{
   int i = 0;
   const int limit = scores_.size();
   if (limit > 0)
   {
      for (i = 0; i < limit; i++)
      {
         oStream << scores_[i] << " ";
         if (i % 5 == 4)
         {
            oStream << endl;
         }
      }

      if (i % 5 != 0)
      {
         oStream << endl;
      }
   }
   else
   {
      oStream << " empty array ";
   }

   return oStream;
}

// friends

// use string version of operator>>()
istream& operator>>(istream& inputStream, Student& student)
{
   inputStream >> student.name_;
   return inputStream;
}

// use string friend getline(ostream &, const string &)
istream& getline(istream& inputStream, Student& student)
{
   getline(inputStream, student.name_);
   return inputStream;
}

// use string version of operator<<()
ostream& operator<<(ostream& oStream, const Student& student)
{
   oStream << "Scores for " << student.name_ << ":\n";
   student.arr_out(oStream); // use private method for scores
   return oStream;
}
