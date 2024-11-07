import std;

using namespace std;

class IsDoable
{
public:
   void doit() const
   {
      println("IsDoable::doit()");
   }
};

class Derived : public IsDoable
{
};

template <typename T>
void callDoit(const T& type)
{
   if constexpr (requires { type.doit(); })
   {
      type.doit();
   }
   else
   {
      println("Cannot call doit()!");
   }
}

int main()
{
   Derived d;
   callDoit(d);
   callDoit(123);
}
