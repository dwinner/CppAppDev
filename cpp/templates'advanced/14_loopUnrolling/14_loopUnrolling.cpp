import std;

using namespace std;

template <int I>
class Loop
{
public:
   template <typename FuncType>
   static void run(FuncType func)
   {
      Loop<I - 1>::run(func);
      func(I);
   }
};

template <>
class Loop<0>
{
public:
   template <typename FuncType>
   static void run(FuncType /* func */)
   {
   }
};

void doWork(int i)
{
   println("doWork({})", i);
}

int main()
{
   Loop<3>::run(doWork);
}
