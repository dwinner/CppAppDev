import std;

using namespace std;

class Foo
{
public:
   explicit Foo(string str, int i) : str_{move(str)}, int_{i}
   {
   }

private:
   string str_;
   int int_;
};

int main()
{
   tuple myTuple{"Hello world.", 42};
   auto foo{make_from_tuple<Foo>(myTuple)};

   return 0;
}
