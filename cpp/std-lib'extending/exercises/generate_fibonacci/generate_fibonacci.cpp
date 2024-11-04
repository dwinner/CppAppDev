import std;

using namespace std;

template <typename OutputIterator>
void GenerateFibonacci(OutputIterator first, OutputIterator last)
{
   typename OutputIterator::value_type a{0};
   typename OutputIterator::value_type b{1};

   auto iter{first};

   if (iter != last)
   {
      *iter = a;
      ++iter;
   }
   else
   {
      return;
   }

   if (iter != last)
   {
      *iter = b;
      ++iter;
   }
   else
   {
      return;
   }

   generate(iter, last,
            [&a, &b]
            {
               auto next{a + b};
               a = b;
               b = next;
               return next;
            });
}

int main()
{
   vector<int> fibonacci(24);
   GenerateFibonacci(begin(fibonacci), end(fibonacci));
   for (const auto& fibVal : fibonacci)
   {
      print("{} ", fibVal);
   }

   println("");
}
