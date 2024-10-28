module empDb;

import std;

using namespace empNs;
using namespace std;

namespace empStore
{
   void Database::add(Person aPerson)
   {
      staff_.emplace_back(aPerson);
   }

   void Database::save(std::string_view aFileName)
   {
      ofstream outFile{aFileName.data(), ios_base::trunc};
      if (!outFile.good())
      {
         println(cerr, "Error while opening file '{}'", aFileName);
         return;
      }

      for (const auto& person : staff_)
      {
         string fmtPerson = format("\"{}\" \"{}\"",
                                   person.getFirstName(),
                                   person.getLastName());
         outFile << fmtPerson << '\n';
      }

      outFile.close();
   }

   void Database::load(std::string_view aFileName)
   {
      ifstream inFile{aFileName.data()};
      if (!inFile.good())
      {
         println(cerr, "Error while opening file '{}'", aFileName);
         return;
      }

      do
      {
         string personStr;
         getline(inFile, personStr, '\n');
         istringstream strStream{personStr};

         string firstName;
         string lastName;
         strStream >> quoted(firstName) >> quoted(lastName);
         if (strStream)
         {
            Person person;
            person.setFirstName(firstName);
            person.setLastName(lastName);
            staff_.emplace_back(person);
         }
      }
      while (inFile.good() && !inFile.eof());
   }

   void Database::clear()
   {
      staff_.clear();
   }

   std::ostream& operator<<(std::ostream& oStream, const Database& database)
   {
      for (const auto& person : database.staff_)
      {
         oStream << person << endl;
      }

      return oStream;
   }
}
