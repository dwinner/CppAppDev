#include <ranges>
#include <span>
#include <vector>
#include <print>

using namespace std;

template<typename T> concept arithmetic = std::is_arithmetic_v<T>;

template<arithmetic TCalc>
double average(span<TCalc> aSpan)
{
   if (aSpan.empty())
   {
      return {};
   }

   double accum = 0.0;
   for (const auto &spanItem: aSpan)
   {
      accum += spanItem;
   }

   return accum / (double) aSpan.size();
}

int main()
{
   vector<double> vec{11, 22, 33, 44, 55, 66};
   array<int, 5> arr{11, 22, 33, 44, 55};

   span<double> vecSpan = vec;
   println("Avg on vector: {}", average(vecSpan));

   span<int> arrSpan = arr;
   println("Avg on array: {}", average(arrSpan));

   return 0;
}
