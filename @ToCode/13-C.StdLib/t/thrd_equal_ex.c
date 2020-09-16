// thrd_equal_ex.c : thrd_equal() example
// -------------------------------------------------------------

#include <threads.h>  // int thrd_equal(thrd_t thr1, thrd_t thr2);
#include <stdio.h>

thrd_t mainThrd;

int func(void)
{
    if( thrd_equal( thrd_current(), mainThrd) )
    { puts("Main thread here ...");  return 0; }
    else
    { puts("Other thread here ..."); return 1; }
}

int main()
{
    thrd_t th;

    mainThrd = thrd_current();

    if ( thrd_create(&th, (thrd_start_t)func, NULL) != thrd_success)
    { fprintf(stderr, "Error creating thread.\n"); return -1; }

    func();
    thrd_join(th, NULL);

    return 0;
}
