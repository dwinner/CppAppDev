import std;

using namespace std;

void AtomicMin(atomic<int>& a, const int b)
{
   int expected{a.load()};
   int desired{min(expected, b)};
   while (!a.compare_exchange_strong(expected, desired))
   {
      desired = min(expected, b);
   }
}

int main()
{
   atomic<int> value1{10};
   AtomicMin(value1, 42);
   println("Min(10, 42) = {}", value1.load());

   atomic<int> value2{84};
   AtomicMin(value2, 42);
   println("Min(84, 42) = {}", value2.load());
}
