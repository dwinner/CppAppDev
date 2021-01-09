// atomic_thread_fence_ex.c : atomic_thread_fence() example
// A variation on the example at atomic_load() in this chapter, 
// but using an acquire fence.
// -------------------------------------------------------------

#include <stdatomic.h>
// void atomic_thread_fence( memory_order order);

#include <threads.h>
#include <stdio.h>
#include <stdlib.h>

struct Data { double x; } data[10];         // Shared data
atomic_int ai = ATOMIC_VAR_INIT(0);

void thrdFunc(void) 
{
    for( int i = 0; i < 10; ++i)             // Operation A
       data[i].x = 0.5 *i;
//  atomic_fetch_add_explicit( &ai, 10, memory_order_release);
//  Replacing above line with:
    atomic_thread_fence(memory_order_release);
    atomic_fetch_add_explicit( &ai, 10, memory_order_relaxed);
}

int main(void)
{
    thrd_t th;
    if( thrd_create( &th, (thrd_start_t)thrdFunc, NULL) != thrd_success)
    {
        fprintf(stderr,"Thread-Fehler!\n"); return -1;
    }
    thrd_yield();
    puts("main..............................................\n"
     "..................................................");

    int n1 = 0;
    // ...
    int n2 = atomic_load_explicit(&ai, memory_order_relaxed);
    if( n2 > n1)
    {
        atomic_thread_fence(memory_order_acquire);
        for( int i = n1; i < n2; ++i)       // Operation B.
           printf("%8.2lf", data[i].x);     // Process the data.
        putchar('\n');
        n1 = n2;
    }
    else                                    // No fence necessary.
        printf("\nNo new data available.\n");

    thrd_join(th, NULL);
    return 0;
}
