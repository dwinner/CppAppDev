#ifndef CLASSES_COMPOSITION_STUDENT_H
#define CLASSES_COMPOSITION_STUDENT_H

#include <string>
#include <valarray>
#include <iostream>

class Student
{
   typedef std::valarray<double> ArrayDb;
   const std::string defaultName_ = "Null Student";

public:
   Student()
      : name_(defaultName_)
   {
   }

   explicit Student(const std::string& studentName)
      : name_(studentName)
   {
   }

   explicit Student(int scoresNumber)
      : name_(defaultName_),
        scores_(scoresNumber)
   {
   }

   Student(const std::string& studentName, int scoresNumber)
      : name_(studentName),
        scores_(scoresNumber)
   {
   }

   Student(const std::string& studentName, const ArrayDb& arrayDb)
      : name_(studentName),
        scores_(arrayDb)
   {
   }

   Student(const char* studentName, const double* scores, int scoresNumber)
      : name_(studentName),
        scores_(scores, scoresNumber)
   {
   }

   ~Student() = default;

   double average() const;

   const std::string& getName() const;

   double& operator[](int index);

   double operator[](int index) const;

   // friends - input
   friend std::istream& operator>>(std::istream& inputStream, Student& student); // 1 word

   friend std::istream& getline(std::istream& inputStream, Student& student); // 1 line

   // output
   friend std::ostream& operator<<(std::ostream& oStream, const Student& student);

private:
   std::string name_; // contained object
   ArrayDb scores_; // contained object   
   std::ostream& arr_out(std::ostream& oStream) const; // private method for scores output
};

#endif //CLASSES_COMPOSITION_STUDENT_H
