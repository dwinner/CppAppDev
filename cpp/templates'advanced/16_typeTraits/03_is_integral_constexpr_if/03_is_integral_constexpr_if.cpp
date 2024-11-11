import std;

using namespace std;

template <typename T>
void process(const T& type)
{
   if constexpr (is_integral_v<T>)
   {
      println("{} is an integral type.", type);
   }
   else
   {
      println("{} is a non-integral type.", type);
   }
}

int main()
{
   process(123);
   process(2.2);
   process("Test"s);
}
