/**
 * atomic_flag_test_and_set() example
 * A spin-lock using atomic_flag_test_and_set().
 */

#include <atomic>
#include <thread>
#include <cstdio>
#include <cstdlib>

/**
 * false if not locked; true if locked.
 */
std::atomic_flag lock;// = ATOMIC_FLAG_INIT;

void th_func(char *msg)
{
   static int count; // Initial value is 0
   while (atomic_flag_test_and_set(&lock))
   {   // Spin until we lock.
   }

   ++count; // Critical section ...
   printf("%3u. %s\n", count, msg);

   atomic_flag_clear(&lock);  // Release lock.
}

#define NUM_THREADS 10

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
      th_arr[i].th = new std::thread(th_func, th_arr[i].msg);
      if (th_arr[i].th == nullptr)
      {
         return EXIT_FAILURE;
      }
   }

   for (auto &item : th_arr)
   {
      item.th->join();
   }

   return EXIT_SUCCESS;
}
