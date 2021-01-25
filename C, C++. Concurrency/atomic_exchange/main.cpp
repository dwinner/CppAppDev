/**
 * atomic_exchange() example:
 * Implements a spin-lock mutex using atomic_exchange().
 */

#include <atomic>
#include <thread>
#include <cstdio>
#include <cstdlib>

/**
 * false if not locked; true if locked.
 */
std::atomic_bool lock = ATOMIC_VAR_INIT(false);

void func(char *msg)
{
   // Initial value is 0.
   static int count;

   // Spin until we lock.
   while (atomic_exchange(&lock, true))
   {}

   // Critical section...
   ++count;
   printf("%3u. %s\n", count, msg);

   // Release the lock.
   lock = false;
}

#define NUM_THREADS 20

int main()
{
   struct
   {
      std::thread *th;
      char msg[32];
   } th_arr[NUM_THREADS];

   for (int i = 0; i < NUM_THREADS; ++i)
   {
      sprintf(th_arr[i].msg, "Thread %2u", i);
      th_arr[i].th = new std::thread(func, th_arr[i].msg);
   }

   for (auto &item : th_arr)
   {
      item.th->join();
   }

   return EXIT_SUCCESS;
}
