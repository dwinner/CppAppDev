// Example 14-2. Concurrent memory access without synchronization
// inc_dec.c

#include <stdio.h>
#include <threads.h>
//#include <stdatomic.h>

#define COUNT 10000000L

long counter = 0;
//_Atomic long counter = ATOMIC_VAR_INIT(0L);

void incFunc(void) { for (long i = 0; i < COUNT; ++i) ++counter; }
void decFunc(void) { for (long i = 0; i < COUNT; ++i) --counter; }

int main(void)
{
    clock_t cl = clock();
    thrd_t th1, th2;

    if( thrd_create(&th1, (thrd_start_t)incFunc, NULL) != thrd_success
        || thrd_create(&th2, (thrd_start_t)decFunc, NULL) != thrd_success)
    {
        fprintf(stderr,"Error creating thread\n"); return -1;
    }
    thrd_join(th1, NULL);
    thrd_join(th2, NULL);

    printf("Counter: %ld \t", counter);
    printf("CPU time: %ld ms\n", (clock()-cl)*1000L/CLOCKS_PER_SEC);

    return 0;
}
