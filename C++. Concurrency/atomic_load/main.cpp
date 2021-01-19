/**
 * atomic_load() example
 */

#include <atomic>
#include <thread>
#include <cstdio>

/**
 * Shared data
 */
struct Data
{
   double x;
} data[10];
std::atomic_int ai = ATOMIC_VAR_INIT(0);

void thrdFunc()
{
   // Operation A
   for (int i = 0; i < 10; ++i)
   {
      data[i].x = 0.5 * i;
   }

   atomic_store_explicit(&ai, 10, std::memory_order_release);
}

int main()
{
   std::thread th(thrdFunc);
   std::this_thread::yield();

   puts("main..............................................\n"
        "..................................................");

   int n = atomic_load_explicit(&ai, std::memory_order_acquire);
   if (n > 0)
   {
      // Operation B
      for (int i = 0; i < n; ++i)
      {
         printf("%8.2lf", data[i].x);
      }

      putchar('\n');
   }
   else
   {
      printf("\nData not yet available.\n");
   }

   th.join();

   return 0;
}
