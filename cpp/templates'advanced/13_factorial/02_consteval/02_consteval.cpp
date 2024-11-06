import std;

using namespace std;

consteval unsigned long long Factorial(const int number)
{
   if (number == 0)
   {
      return 1;
   }

   return number * Factorial(number - 1);
}

int main()
{
   constexpr int num = 6;
   println("{}", Factorial(num));
}
