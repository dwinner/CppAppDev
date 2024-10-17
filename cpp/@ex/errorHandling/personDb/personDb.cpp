import person;
import person_database;
import std;
import file_errors;

#include <cstdlib>

using namespace std;
using namespace fileErrors;

int main()
{
   // Fill a database.
   Database db;
   db.add(Person{"John", "Doe"});
   db.add(Person{"Marc", "Gregoire", "Mg"});
   db.add(Person{"Peter", "Van Weert", "PVW"});

   // Output all persons in the database to standard output.
   println("Initial database contents:");
   db.outputAll(cout);

   const auto dbName = "person.db";

   // Save the database to a file.
   try
   {
      db.save(dbName);
   }
   catch (const FileErrorBase& fileError)
   {
      println(cerr, "{}", fileError.what());
      return EXIT_FAILURE;
   }

   // Clear the database.
   db.clear();
   println("\nDatabase contents after clearing:");
   db.outputAll(cout);

   // Load database from file.
   println("\nLoading database from file...");
   try
   {
      db.load(dbName);
   }
   catch (const FileErrorBase& fileError)
   {
      println(cerr, "{}", fileError.what());
      return EXIT_FAILURE;
   }

   println("\nDatabase contents after loading from file:");
   db.outputAll(cout);

   return EXIT_SUCCESS;
}
