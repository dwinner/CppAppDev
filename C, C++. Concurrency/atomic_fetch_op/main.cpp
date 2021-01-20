/**
 * atomic_fetch_op() example:
 * Implements a semaphore using atomic_fence_sub() and atomic_fence_add().
 */

#include <atomic>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <chrono>

using namespace std::chrono_literals;

#define MAX_READERS 5          // Number of data-reading threads.

/**
 * Semaphore counts the number of idle resources (here: readers),
 * or -1 if locked by writer. Busy readers == MAX_READERS - count.
 */
std::atomic_int count = ATOMIC_VAR_INIT(MAX_READERS);

/**
 * Valid data are positive.
 */
int data = 0;

void readerFunc(const int *idPtr)
{
   int id = *idPtr;

   while (true)
   {
      // Check semaphore; decrement and read if count > 0.
      while (std::atomic_fetch_sub(&count, 1) <= 0)
      {
         std::atomic_fetch_add(&count, 1);
         std::this_thread::yield();
      }

      // Read valid data.
      if (data > 0)
      {
         printf("Reader %d is reading %d\n", id, data);
      }

      // End marker: stop looping.
      if (data < 0)
      {
         break;
      }

      // Release our reader slot.
      std::atomic_fetch_add(&count, 1);
      std::this_thread::sleep_for(1ms);
   }
}

void writerFunc() // Writes positive values; ends with a negative value.
{
   const int N = 20; // Number of data values to write.
   for (int n = 0; n <= N; ++n)
   {
      // Prepare data or end marker.
      int d = n < N ? 10 + n : -1;

      // When no readers are busy, lock the semaphore (count = -1):
      while (atomic_fetch_sub(&count, MAX_READERS + 1) != MAX_READERS)
      {
         atomic_fetch_add(&count, MAX_READERS + 1);
      }

      // Critical section.
      printf("Writer is writing %d\n", d);
      data = d;

      // Release the semaphores.
      atomic_fetch_add(&count, MAX_READERS + 1);

      // Simulate data production.
      std::this_thread::sleep_for(1ms);
   }
}

int main()
{
   using namespace std;

   thread *writerThread;
   struct
   {
      thread *readerThread;
      int id;
   } th_arr[MAX_READERS];

   // Writer thread:
   writerThread = new thread(writerFunc);

   // Reader threads:
   for (int i = 0; i < MAX_READERS; ++i)
   {
      th_arr[i].id = i;
      th_arr[i].readerThread = new thread(readerFunc, &th_arr[i].id);
   }

   writerThread->join();

   for (auto &item : th_arr)
   {
      item.readerThread->join();
   }

   return EXIT_SUCCESS;
}
