#include <iostream>
#include <format>

using namespace std;

class Simple
{
public:
   Simple()
   {
      std::cout << std::format("Simple constructor called!") << std::endl;
   }

   ~Simple()
   {
      std::cout << std::format("Simple destructor called!") << std::endl;
   }
};

int main()
{
   Simple *mySimpleArray{new Simple[4]};
   // Use mySimpleArray...
   delete[] mySimpleArray;
   mySimpleArray = nullptr;

   const size_t size{4};
   Simple **mySimplePtrArray{new Simple *[size]};

   // Allocate an object for each pointer.
   for (size_t i{0}; i < size; ++i)
   {
      mySimplePtrArray[i] = new Simple{};
   }

   // Use mySimplePtrArray ...

   // Delete each allocated object.
   for (size_t i{0}; i < size; ++i)
   {
      delete mySimplePtrArray[i];
      mySimplePtrArray[i] = nullptr;
   }

   // Delete the array itself.
   delete[] mySimplePtrArray;
   mySimplePtrArray = nullptr;

   return 0;
}
