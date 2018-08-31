// atomic_flag_test_and_set_ex.c : atomic_flag_test_and_set() example
// A spin-lock using atomic_flag_test_and_set().
// -------------------------------------------------------------

#include <stdatomic.h>
// _Bool atomic_flag_test_and_set( volatile atomic_flag *obj);
// _Bool atomic_flag_test_and_set_explicit( volatile atomic_flag *obj,
//                                          memory_order order);
// void atomic_flag_clear( volatile atomic_flag *obj);
// void atomic_flag_clear_explicit( volatile atomic_flag *obj,
//                                  memory_order order);

#include <threads.h>
#include <stdio.h>
#include <stdlib.h>

atomic_flag lock = ATOMIC_FLAG_INIT;    // false if not locked;
                                        // true if locked.
void th_func(char *msg)
{
    static int count;                   // Initial value is 0
    while( atomic_flag_test_and_set(&lock))   // Spin until we lock.
        ;
    ++count;                            // Critical section ...
    printf("%3u. %s\n", count, msg);
    atomic_flag_clear(&lock);           // Release lock.
}


#define NUM_THREADS 10

int main()
{
    struct { thrd_t th; char msg[32]; } th_arr[NUM_THREADS];

    for( int i = 0; i < NUM_THREADS; ++i)
    {
       sprintf( th_arr[i].msg,"Thread %2u", i);
       if( thrd_create( &th_arr[i].th, (thrd_start_t)th_func,
                        (void*)th_arr[i].msg) != thrd_success)
           return EXIT_FAILURE;
    }
    for( int i = 0; i < NUM_THREADS; ++i)
        thrd_join( th_arr[i].th, NULL);

    return EXIT_SUCCESS;
}
