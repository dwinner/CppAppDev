import std;

using namespace std;

template <unsigned int TNum>
class Fibonacci
{
public:
   static constexpr unsigned long long value{
      Fibonacci<TNum - 2>::value + Fibonacci<TNum - 1>::value
   };
};

template <>
class Fibonacci<0>
{
public:
   static constexpr unsigned long long value{0};
};

template <>
class Fibonacci<1>
{
public:
   static constexpr unsigned long long value{1};
};

// Bonus: variable template.
template <unsigned int TNum>
inline constexpr unsigned long long Fibonacci_v = Fibonacci<TNum>::value;

int main()
{
   println("{}", Fibonacci<0>::value);
   println("{}", Fibonacci<1>::value);
   println("{}", Fibonacci_v<2>);
   println("{}", Fibonacci_v<3>);
   println("{}", Fibonacci_v<4>);
   println("{}", Fibonacci_v<5>);
   println("{}", Fibonacci_v<6>);
   println("{}", Fibonacci_v<7>);
   println("{}", Fibonacci_v<8>);
   println("{}", Fibonacci_v<9>);
   println("{}", Fibonacci_v<10>);
   println("{}", Fibonacci_v<11>);
}
