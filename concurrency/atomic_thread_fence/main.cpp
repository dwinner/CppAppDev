/**
 * atomic_thread_fence() example:
 * A variation on the example at atomic_load() in this chapter,
 * but using an acquire fence.
 */

#include <iostream>
#include <atomic>
#include <thread>

struct Data
{
   double x;
} data[10];         // Shared data

std::atomic_int ai = ATOMIC_VAR_INIT(0);

void threadFunc()
{
   // Operation A
   for (int i = 0; i < 10; ++i)
   {
      data[i].x = 0.5 * i;
   }

   //  atomic_fetch_add_explicit( &ai, 10, memory_order_release);
   //  Replacing above line with:

   atomic_thread_fence(std::memory_order_release);
   atomic_fetch_add_explicit(&ai, 10, std::memory_order_relaxed);
}

int main()
{
   std::thread th(threadFunc);
   std::this_thread::yield();

   puts("main..............................................\n"
        "..................................................");

   int n1 = 0;

   // ...
   int n2 = std::atomic_load_explicit(&ai, std::memory_order_relaxed);
   if (n2 > n1)
   {
      std::atomic_thread_fence(std::memory_order_acquire);
      for (int i = n1; i < n2; ++i)
      {
         // Operation B.
         printf("%8.2lf", data[i].x);
         // Process the data.
      }

      putchar('\n');
      n1 = n2;
   }
   else
   {  // No fence necessary.
      printf("\nNo new data available.\n");
   }

   th.join();

   return 0;
}
