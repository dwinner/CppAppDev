import std;
import errorHandling;

using namespace std;
using namespace biDir;

void ChangeNumberForId(const string& filename, int id, string_view newNumber);

int main()
{
   try
   {
      ChangeNumberForId("data.txt", 263, "415-555-3333");
   }
   catch (const FileNotFoundException& fnfEx)
   {
      std::cout << fnfEx.what() << std::endl;
      throw;
   }
}

void ChangeNumberForId(const string& filename, const int id, const string_view newNumber)
{
   fstream ioData{filename};
   if (!ioData)
   {
      const string errorMsg = std::format("Error while opening file {}.", filename);
      throw FileNotFoundException{errorMsg.c_str()};
   }

   // Loop until the end of file
   while (ioData)
   {
      // Read the next ID.
      int idRead;
      ioData >> idRead;
      if (!ioData)
      {
         break;
      }

      // Check to see if the current record is the one being changed.
      if (idRead == id)
      {
         // Seek the write position to the current read position.
         ioData.seekp(ioData.tellg());

         // Output a space, then the new number.
         ioData << " " << newNumber;
         break;
      }

      // Read the current number to advance the stream.
      string number;
      ioData >> number;
   }
}
