#include <print>

void play();

int main()
{
   play();
   return 0;
}

void play()
{
   const size_t elementNumber{10};
   auto values = std::make_unique<int[]>(elementNumber);

   for (int i{0}; i < elementNumber; ++i)
   {
      values[i] = i;
   }

   for (int i = 0; i < elementNumber; ++i)
   {
      std::print("{} ", values[i]);
   }
}
