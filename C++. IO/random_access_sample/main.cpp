/**
 * random access to a binary file
 */

#include <iostream>     // not required by most systems
#include <fstream>
#include <iomanip>
#include <cstdlib>      // (or stdlib.h) for exit()

const int LIM = 20;

struct planet
{
   char name[LIM];      // name of planet
   double population;  // its population
   double g;           // its acceleration of gravity
};

const char *file = "planets.dat";  // ASSUMED TO EXIST (binary.cpp example)

inline void eatLine()
{
   while (std::cin.get() != '\n')
   {
      continue;
   }
}

int main()
{
   using namespace std;
   planet planetRecord{};
   cout << fixed;

   // show initial contents
   fstream finout;     // read and write streams
   finout.open(file, ios_base::in | ios_base::out | ios_base::binary);

   // NOTE: Some Unix systems require omitting | ios::binary
   int ct = 0;
   if (finout.is_open())
   {
      finout.seekg(0);    // go to beginning
      cout << "Here are the current contents of the "
           << file << " file:\n";
      while (finout.read((char *) &planetRecord, sizeof planetRecord))
      {
         cout << ct++ << ": " << setw(LIM) << planetRecord.name << ": "
              << setprecision(0) << setw(12) << planetRecord.population
              << setprecision(2) << setw(6) << planetRecord.g << endl;
      }

      if (finout.eof())
      {
         finout.clear(); // clear eof flag
      }
      else
      {
         cerr << "Error in reading " << file << ".\n";
         exit(EXIT_FAILURE);
      }
   }
   else
   {
      cerr << file << " could not be opened -- bye.\n";
      exit(EXIT_FAILURE);
   }

   // change a record
   cout << "Enter the record number you wish to change: ";
   long rec;
   cin >> rec;
   eatLine();              // get rid of newline
   if (rec < 0 || rec >= ct)
   {
      cerr << "Invalid record number -- bye\n";
      exit(EXIT_FAILURE);
   }

   streampos place = rec * sizeof planetRecord;  // convert to streampos type
   finout.seekg(place);    // random access
   if (finout.fail())
   {
      cerr << "Error on attempted seek\n";
      exit(EXIT_FAILURE);
   }

   finout.read((char *) &planetRecord, sizeof planetRecord);
   cout << "Your selection:\n";
   cout << rec << ": " << setw(LIM) << planetRecord.name << ": "
        << setprecision(0) << setw(12) << planetRecord.population
        << setprecision(2) << setw(6) << planetRecord.g << endl;

   if (finout.eof())
   {
      finout.clear();
   }     // clear eof flag

   cout << "Enter planet name: ";
   cin.get(planetRecord.name, LIM);
   eatLine();
   cout << "Enter planetary population: ";
   cin >> planetRecord.population;
   cout << "Enter planet's acceleration of gravity: ";
   cin >> planetRecord.g;
   finout.seekp(place);    // go back
   finout.write((char *) &planetRecord, sizeof planetRecord) << flush;
   if (finout.fail())
   {
      cerr << "Error on attempted write\n";
      exit(EXIT_FAILURE);
   }

   // show revised file
   ct = 0;
   finout.seekg(0);            // go to beginning of file
   cout << "Here are the new contents of the " << file
        << " file:\n";
   while (finout.read((char *) &planetRecord, sizeof planetRecord))
   {
      cout << ct++ << ": " << setw(LIM) << planetRecord.name << ": "
           << setprecision(0) << setw(12) << planetRecord.population
           << setprecision(2) << setw(6) << planetRecord.g << endl;
   }

   finout.close();
   cout << "Done.\n";

   return 0;
}
