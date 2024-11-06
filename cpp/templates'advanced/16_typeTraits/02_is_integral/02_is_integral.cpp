import std;

using namespace std;

template <typename T>
void processHelper(const T& type, true_type)
{
   println("{} is an integral type.", type);
}

template <typename T>
void processHelper(const T& type, false_type)
{
   println("{} is a non-integral type.", type);
}

template <typename T>
void process(const T& type)
{
   processHelper(type, is_integral<T>{});
}

int main()
{
   process(123);
   process(2.2);
   process("Test"s);
}
