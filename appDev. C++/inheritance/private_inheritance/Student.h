#ifndef PRIVATE_INHERITANCE_STUDENT_H
#define PRIVATE_INHERITANCE_STUDENT_H

#include <iostream>
#include <valarray>
#include <string>

class Student : std::string, std::valarray<double>
{
   typedef std::valarray<double> ArrayDb;

   // private method for scores output
   std::ostream& arr_out(std::ostream& outputStream) const;

public:
   Student()
      : std::string("Null Student"),
        ArrayDb()
   {
   }

   explicit Student(const std::string& studentName)
      : std::string(studentName),
        ArrayDb()
   {
   }

   explicit Student(int scoreCount)
      : std::string("Nully"),
        ArrayDb(scoreCount)
   {
   }

   Student(const std::string& studentName, int scoreCount)
      : std::string(studentName),
        ArrayDb(scoreCount)
   {
   }

   Student(const std::string& studentName, const ArrayDb& arrayDb)
      : std::string(studentName),
        ArrayDb(arrayDb)
   {
   }

   Student(const char* studentName, const double* scoreValues, int scoreCount)
      : std::string(studentName),
        ArrayDb(scoreValues, scoreCount)
   {
   }

   ~Student()
   {
   }

   double average() const;

   double& operator[](int index);

   double operator[](int index) const;

   const std::string& getStudentName() const;

   // friends
   // input
   friend std::istream& operator>>(std::istream& inputStream, Student& student); // 1 word
   friend std::istream& getline(std::istream& inputStream, Student& student); // 1 line

   // output
   friend std::ostream& operator<<(std::ostream& outputStream, const Student& student);
};

#endif //PRIVATE_INHERITANCE_STUDENT_H
