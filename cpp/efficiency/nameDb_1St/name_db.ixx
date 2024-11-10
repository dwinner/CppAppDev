export module name_db;

import std;

export class NameDb
{
public:
   // Reads list of baby names in nameFile to populate the database.
   // Throws invalid_argument if nameFile cannot be opened or read.
   explicit NameDb(const std::string& nameFile);

   // Returns the rank of the name (1st, 2nd, etc).
   // Returns -1 if the name is not found.
   int getNameRank(const std::string& name) const;

   // Returns the number of babies with a given name.
   // Returns -1 if the name is not found.
   int getAbsoluteNumber(const std::string& name) const;

private:
   std::vector<std::pair<std::string, int>> names_;

   // Helper member functions
   bool nameExists(const std::string& name) const;

   void incrementNameCount(const std::string& name);

   void addNewName(const std::string& name);
};
