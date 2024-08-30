#include <iostream>
#include <memory>

using namespace std;

void close(FILE *filePtr)
{
   if (filePtr == nullptr)
   {
      return;
   }

   fclose(filePtr);
   cout << "File closed." << endl;
}

int main()
{
#if defined(_MSC_VER)
   // Disable the following Microsoft Visual C++ warning for this example:
   // C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead.
#pragma warning( disable : 4996)
#endif

   FILE *f{fopen("data.txt", "w")};
   shared_ptr<FILE> filePtr{f, close};
   if (filePtr == nullptr)
   {
      cerr << "Error opening file." << endl;
   }
   else
   {
      cout << "File opened." << endl;
      // Use filePtr
   }

   return 0;
}
