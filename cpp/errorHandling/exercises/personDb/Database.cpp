module person_database;

import std;
import file_errors;

using namespace std;
using namespace fileErrors;

void Database::add(Person person)
{
   persons_.push_back(move(person));
}

void Database::clear()
{
   persons_.clear();
}

void Database::save(const string& filename) const
{
   ofstream outFile{filename, ios_base::trunc};
   if (!outFile)
   {
      throw FileOpenError(filename);
   }

   for (const auto& person : persons_)
   {
      // We need to support spaces in names.
      // So, to be able to read back names later in load(),
      // we simply quote all parts of the name.
      outFile
         << quoted(person.getFirstName())
         << quoted(person.getLastName())
         << quoted(person.getInitials())
         << endl;
   }
}

void Database::load(const string& filename)
{
   ifstream inFile{filename};
   if (!inFile)
   {
      throw FileOpenError(filename);
   }

   size_t lineNum{0};
   while (inFile)
   {
      // Read line by line, so we can skip empty lines.
      // The last line in the file is empty, for example.
      string line;
      getline(inFile, line);
      ++lineNum;
      if (line.empty())
      {
         // Skip empty lines
         continue;
      }

      // Make a string stream and parse it.
      istringstream inLine{line};
      string firstName, lastName, initials;
      inLine >> quoted(firstName) >> quoted(lastName) >> quoted(initials);
      if (inLine.bad())
      {
         throw FileReadError(filename, lineNum);
      }

      // Create a person and add it to the database.
      persons_.push_back(
         Person{move(firstName), move(lastName), move(initials)});
   }
}

void Database::outputAll(ostream& output) const
{
   for (const auto& person : persons_)
   {
      person.output(output);
   }
}
