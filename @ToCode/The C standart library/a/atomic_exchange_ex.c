// atomic_exchange_ex.c : atomic_exchange() example
// Implements a spin-lock mutex using atomic_exchange().
// -------------------------------------------------------------

#include <stdatomic.h>
// _Bool atomic_exchange( volatile A *object, C desired);
// _Bool atomic_exchange_explicit( volatile A *object, C desired,
//                                 memory_order order);

#include <threads.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

atomic_bool lock = ATOMIC_VAR_INIT(false);  // false if not locked;
                                            // true if locked.
void func(char *msg)
{
    static int count;                       // Initial value is 0.
    while( atomic_exchange(&lock, true))    // Spin until we lock.
        ;
    ++count;                                // Critical section ...
    printf("%3u. %s\n", count, msg);
    lock = false;                           // Release the lock.
}

#define NUM_THREADS 20

int main()
{
    struct { thrd_t th; char msg[32]; } th_arr[NUM_THREADS];

    for( int i = 0; i < NUM_THREADS; ++i)
    {
       sprintf( th_arr[i].msg,"Thread %2u", i);
       if( thrd_create( &th_arr[i].th, (thrd_start_t)func,
                        (void*)th_arr[i].msg) != thrd_success)
           return EXIT_FAILURE;
    }
    for( int i = 0; i < NUM_THREADS; ++i)
        thrd_join( th_arr[i].th, NULL);

    return EXIT_SUCCESS;
}
