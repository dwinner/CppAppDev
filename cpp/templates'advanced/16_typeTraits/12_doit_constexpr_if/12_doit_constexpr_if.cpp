import std;

using namespace std;

class IsDoable
{
public:
   virtual void doit() const
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
   if constexpr (is_base_of_v<IsDoable, T>)
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
