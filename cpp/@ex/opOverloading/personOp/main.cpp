#include <iostream>
#include <sstream>
#include <fstream>
#include "Person.hpp"

using namespace std;

int main()
{
   Person person{"John", "Doe"};

   // Write person to standard output console.
   cout << "Directly to output stream: ";
   person.output(cout);

   // Write person to a string stream.
   ostringstream oss;
   person.output(oss);

   // Verify the contents of the string stream.
   cout << "To string stream: ";
   cout << oss.str() << endl;

   // Write person to a file.
   ofstream outFile{"person.txt"};
   person.output(outFile);

   // check insertion and subtraction
   /*Person newEmp;
   cin>>newEmp;
   cout<<newEmp<<endl;

   // check string conversion on a Person
   string fullName=newEmp;
   cout<<fullName<<endl;*/

   // check user-defined literal
   Person empty{""_p};
   Person fNameOnly{"Mike"_p};
   Person fully{"Mike Tayson"_p};

   return 0;
}
