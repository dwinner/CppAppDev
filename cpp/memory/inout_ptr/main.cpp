#include <iostream>
#include <memory>

void println(const char *str);

using namespace std;

using errorCode = int;

errorCode my_alloc(int value, int **data)
{
   *data = new int{value};
   println("Allocated");
   return 0;
}

void println(const char *str)
{
   cout << str << endl;
}

errorCode my_free(const int *data)
{
   delete data;
   println("Freed");
   return 0;
}

int main()
{
   {
      unique_ptr<int, decltype(&my_free)> myIntSmartPtr(nullptr, my_free);
      int *data{nullptr};
      my_alloc(42, &data);
      myIntSmartPtr.reset(data);
   }

   {
      unique_ptr<int, decltype(&my_free)> myIntSmartPtr(nullptr, my_free);
      my_alloc(42, inout_ptr(myIntSmartPtr));
   }

   return 0;
}
