module empDb;

import std;

using namespace empNs;
using namespace std;

namespace empStore
{
   using namespace filesystem;

   void DirDatabase::save(const std::string_view aDirName)
   {
      if (!exists(aDirName))
      {
         create_directory(aDirName);
      }

      for (const auto& person : staff_)
      {
         string personFileFmt{
            format("{}_{}.person",
                   person.getFirstName(),
                   person.getLastName())
         };
         path personPath{aDirName};
         personPath /= personFileFmt;
         if (exists(personPath))
         {
            remove(personPath);
         }

         ofstream currentOut{personPath, ios_base::trunc};
         if (currentOut.good())
         {
            string empToStore = format("\"{}\" \"{}\"",
                                       person.getFirstName(),
                                       person.getLastName());
            currentOut << empToStore;
         }

         currentOut.close();
      }
   }

   void DirDatabase::load(std::string_view aDirName)
   {
      path empDir{aDirName};
      if (!exists(empDir) || !is_directory(empDir))
      {
         return;
      }

      for (auto& entry : directory_iterator{empDir})
      {
         path empPath = entry.path();
         if (string ext = empPath.extension().string(); ext != ".person")
         {
            continue;
         }

         ifstream empInStream{empPath};
         if (empInStream.good())
         {
            string personStr;
            getline(empInStream, personStr);
            istringstream strStream{personStr};
            string firstName, lastName;
            strStream >> quoted(firstName) >> quoted(lastName);
            if (strStream)
            {
               Person person;
               person.setFirstName(firstName);
               person.setLastName(lastName);
               staff_.emplace_back(person);
            }
         }

         empInStream.close();
      }
   }
}
