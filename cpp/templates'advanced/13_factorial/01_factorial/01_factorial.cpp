import std;

using namespace std;

template <int F>
class Factorial
{
public:
   static constexpr unsigned long long value{F * Factorial<F - 1>::value};
};

template <>
class Factorial<0>
{
public:
   static constexpr unsigned long long value{1};
};

int main()
{
   println("{}", Factorial<6>::value);
}
