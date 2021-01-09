// atomic_fetch_ex.c : atomic_fetch_op() example
// Implements a semaphore using atomic_fence_sub() and atomic_fence_add().
// -------------------------------------------------------------

#include <stdatomic.h>
// C atomic_fetch_op( volatile A *object, M operand);
// C atomic_fetch_op_explicit( volatile A *object, M operand, memory_order order);

#include <threads.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_READERS 5          // Number of data-reading threads.

// Semaphore counts the number of idle resources (here: readers),
// or -1 if locked by writer. Busy readers == MAX_READERS - count.
atomic_int count = ATOMIC_VAR_INIT(MAX_READERS);

int data = 0;                  // Valid data are positive.

// 1 millisecond = 1,000,000 nanoseconds
const struct timespec ms = { .tv_nsec = 1000*1000 };

void reader(int* idPtr)
{
    int id = *idPtr;
    while(1)
    {
        // Check semaphore; decrement and read if count > 0.
        while( atomic_fetch_sub(&count, 1) <= 0)
        {  atomic_fetch_add(&count, 1); thrd_yield(); }

        if( data > 0)                  // Read valid data.
            printf("Reader %d is reading %d\n", id, data);
        if( data < 0)                  // End marker: stop looping.
            break;

        atomic_fetch_add(&count, 1);   // Release our reader slot.
        thrd_sleep(&ms,NULL);          // Simulate data processing.
    }
}

void writer(void)  // Writes positive values; ends with a negative value.
{
    const int N = 20;                  // Number of data values to write.
    for( int n = 0; n <= N; ++n)
    {
        int d = n < N ? 10+n : -1;     // Prepare data or end marker.
        // When no readers are busy, lock the semaphore (count = -1):
        while( atomic_fetch_sub(&count,MAX_READERS+1) != MAX_READERS)
            atomic_fetch_add(&count, MAX_READERS+1);

        printf("Writer is writing %d\n", d),     // Critical section.
        data = d;
        atomic_fetch_add(&count, MAX_READERS+1); // Release the
                                                 // semaphores.
        thrd_sleep(&ms,NULL);          // Simulate data production.
    }
}

int main(void)
{
    thrd_t wth;
    struct { thrd_t th; int id; } th_arr[MAX_READERS];

   // Writer thread:
   if( thrd_create( &wth,(thrd_start_t)writer, NULL) != thrd_success)
      return EXIT_FAILURE;

   // Reader threads:
   for( int i = 0; i < MAX_READERS; ++i)
   {
      th_arr[i].id = i;
      if( thrd_create( &th_arr[i].th, (thrd_start_t)reader,
                       &th_arr[i].id) != thrd_success)
         return EXIT_FAILURE;
   }

   thrd_join( wth, NULL);
   for( int i = 0; i < MAX_READERS; ++i)
       thrd_join( th_arr[i].th, NULL);
   return EXIT_SUCCESS;
}
