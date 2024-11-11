module name_db;

import std;

using namespace std;

// Reads the names from the file and populates the database.
// The database is a vector of name/count pairs, storing the
// number of times each name shows up in the raw data.
NameDb::NameDb(const string& nameFile)
{
   // Open the file and check for errors.
   ifstream inputFile{nameFile};
   if (!inputFile)
   {
      throw invalid_argument{"Unable to open file"};
   }

   // Read the names one at a time.
   string name;
   while (inputFile >> name)
   {
      // Look up the name in the database so far.
      if (nameExists(name))
      {
         // If the name exists in the database, just increment the count.
         incrementNameCount(name);
      }
      else
      {
         // If the name doesn't yet exist, add it with a count of 1.
         addNewName(name);
      }
   }
}

// Returns true if the name exists in the database, false otherwise.
bool NameDb::nameExists(const string& name) const
{
   // Iterate through the vector of names looking for the name.
   for (const auto& key : names_ | views::keys)
   {
      if (key == name)
      {
         return true;
      }
   }

   return false;
}

// Precondition: name exists in the vector of names.
// Postcondition: the count associated with name is incremented.
void NameDb::incrementNameCount(const string& name)
{
   for (auto& [first, second] : names_)
   {
      if (first == name)
      {
         second += 1;
         return;
      }
   }
}

// Adds a new name to the database.
void NameDb::addNewName(const string& name)
{
   names_.emplace_back(name, 1);
}

// Returns the rank of the name.
// First looks up the name to obtain the number of babies with that name.
// Then iterates through all the names, counting all the names with a higher
// count than the specified name. Returns that count as the rank.
int NameDb::getNameRank(const string& name) const
{
   // Make use of the getAbsoluteNumber() member function.
   const int num{getAbsoluteNumber(name)};

   // Check if we found the name.
   if (num == -1)
   {
      return -1;
   }

   // Now count all the names in the vector that have a
   // count higher than this one. If no name has a higher count,
   // this name is rank number 1. Every name with a higher count
   // decreases the rank of this name by 1.
   int rank{1};
   for (const auto& val : names_ | views::values)
   {
      if (val > num)
      {
         ++rank;
      }
   }

   return rank;
}

// Returns the count associated with the given name.
int NameDb::getAbsoluteNumber(const string& name) const
{
   for (const auto& [first, second] : names_)
   {
      if (first == name)
      {
         return second;
      }
   }

   return -1;
}
