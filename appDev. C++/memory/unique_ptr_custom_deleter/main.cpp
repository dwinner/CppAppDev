#include <iostream>
#include <memory>

using namespace std;

int *my_alloc(int value)
{
   return new int{value};
}

void my_free(const int *p)
{
   delete p;
}

int main()
{
   std::unique_ptr<int, decltype(&my_free)> myIntSmartPtr{my_alloc(42), my_free};
}
