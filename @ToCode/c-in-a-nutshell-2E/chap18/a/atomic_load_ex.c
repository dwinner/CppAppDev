// atomic_load_ex.c : atomic_load() example
// -------------------------------------------------------------

#include <stdatomic.h>
// C atomic_load( volatile A *obj);
// C atomic_load_explicit( volatile A *obj, 
//                         memory_order order);
// void atomic_store( volatile A *obj, C desired);
// void atomic_store_explicit( volatile A *obj, C desired,
//                             memory_order order);

#include <threads.h>
#include <stdio.h>
#include <stdlib.h>

struct Data { double x; } data[10];         // Shared data
atomic_int ai = ATOMIC_VAR_INIT(0);

void thrdFunc(void) 
{
   for( int i = 0; i < 10; ++i)             // Operation A
       data[i].x = 0.5 *i;
   atomic_store_explicit( &ai, 10, memory_order_release);
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

    int n = atomic_load_explicit(&ai, memory_order_acquire);
    if( n > 0)
    {
       for( int i = 0; i < n; ++i)          // Operation B
          printf("%8.2lf", data[i].x);
       putchar('\n');
    }
    else
       printf("\nData not yet available.\n");

    thrd_join(th, NULL);
    return 0;
}
