import std;

using namespace std;

class Foo
{
public:
   explicit Foo(int i, string s, bool b)
      : intVal_{i}, strVal_{move(s)}, boolVal_{b}
   {
   }

   // Explicitly default operator<=>
   //auto operator<=>(const Foo& rhs) const = default;

   // Compare a subset of the data members.
   auto operator<=>(const Foo& rhs) const
   {
      return tie(intVal_, strVal_) <=> tie(rhs.intVal_, rhs.strVal_);
   }

private:
   int intVal_;
   string strVal_;
   bool boolVal_;
};

int main()
{
   Foo f1{42, "Hello", false};
   Foo f2{42, "World", false};
   println("{}", (f1 < f2)); // Outputs true
   println("{}", (f2 > f1)); // Outputs true
}
