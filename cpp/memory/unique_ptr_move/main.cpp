#include <iostream>
#include <memory>

using namespace std;

class Foo
{
public:
   Foo(unique_ptr<int> data)
       : _data{std::move(data)}
   {}

private:
   unique_ptr<int> _data;
};

int main()
{
   auto myIntSmartPtr{make_unique<int>(42)};
   Foo f{std::move(myIntSmartPtr)};

   return 0;
}
