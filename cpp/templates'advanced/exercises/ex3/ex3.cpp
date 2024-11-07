import std;

using namespace std;

consteval unsigned long long Fibonacci(const unsigned int number)
{
   if (number == 0)
   {
      return 0;
   }

   if (number == 1)
   {
      return 1;
   }

   unsigned long long current{0};
   unsigned long long next{1};
   unsigned long long result{0};
   for (unsigned int i{1}; i < number; ++i)
   {
      result = current + next;
      current = next;
      next = result;
   }

   return result;
}

int main()
{
   println("{}", Fibonacci(0));
   println("{}", Fibonacci(1));
   println("{}", Fibonacci(2));
   println("{}", Fibonacci(3));
   println("{}", Fibonacci(4));
   println("{}", Fibonacci(5));
   println("{}", Fibonacci(6));
   println("{}", Fibonacci(7));
   println("{}", Fibonacci(8));
   println("{}", Fibonacci(9));
   println("{}", Fibonacci(10));
   println("{}", Fibonacci(11));
}
