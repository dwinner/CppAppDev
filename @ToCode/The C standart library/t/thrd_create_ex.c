// thrd_create_ex.c : thrd_create() example
// -------------------------------------------------------------

#include <threads.h>  // int thrd_create(thrd_t *thr, thrd_start_t func, void *arg);
#include <stdio.h>

int th_func(void * arg)         // The thread function.
{
    puts("Hello from th_func ...");
    ++*(int*)arg;
    return 0;
}

int main()
{
    thrd_t th; int n = 1;

    if ( thrd_create(&th, th_func, &n) != thrd_success) {
       fprintf(stderr, "Error creating thread.\n"); return -1;
    }
    puts("Main thread here ...");

    thrd_join(th, NULL);
    printf("The value of n is %d\n", n);       // n == 2

    return 0;
}
