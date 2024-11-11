import std;

using namespace std;

unsigned long long Fibonacci(const unsigned int number)
{
   if (number == 0)
   {
      return 0;
   }

   if (number == 1)
   {
      return 1;
   }

   unsigned long long prev{0};
   unsigned long long current{1};
   unsigned long long result{0};
   for (unsigned int i{1}; i < number; ++i)
   {
      result = prev + current;
      prev = current;
      current = result;
   }

   return result;
}

int main()
{
   // Indices of Fibonacci numbers to calculate.
   vector fibonacciNumbersToCalculate{4, 9, 14, 17};

   // Launch threads to calculate the required numbers concurrently.
   vector<future<unsigned long long>> futures;
   for (auto& index : fibonacciNumbersToCalculate)
   {
      futures.push_back(async(launch::async, Fibonacci, index));
   }

   // Wait for all threads to finish and collect results.
   vector<unsigned long long> fibonacciNumbers;
   for (auto& fut : futures)
   {
      fibonacciNumbers.push_back(fut.get());
   }

   // Print the calculated numbers.
   for (const auto& num : fibonacciNumbers)
   {
      print("{} ", num);
   }

   println("");

   // Calculate their sum.
   auto foldLeft = ranges::fold_left(fibonacciNumbers, 0ull, std::plus<>{});
   println("Their sum: {}", foldLeft);
}
