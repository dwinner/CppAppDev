// call_once_ex.c : call_once() example
// -------------------------------------------------------------

#include <threads.h>  // void call_once(once_flag *flag, void (*func)(void));
#include <stdio.h>

once_flag flag = ONCE_FLAG_INIT;

void doOnce(void) { puts("Function doOnce()."); }

int th_func(void * arg)
{
    puts((char*)arg);
    call_once(&flag, doOnce);
    return 0;
}

int main()
{
    thrd_t th1, th2, th3;

    if(    thrd_create(&th1, th_func, "Thread 1") != thrd_success 
        || thrd_create(&th2, th_func, "Thread 2") != thrd_success
        || thrd_create(&th3, th_func, "Thread 3") != thrd_success)
    {
        fprintf(stderr, "Error creating thread.\n");
        return 0xff;
    }
    puts("Hello ...");

    thrd_join(th1, NULL);
    thrd_join(th2, NULL);
    thrd_join(th3, NULL);

    return 0;
}
