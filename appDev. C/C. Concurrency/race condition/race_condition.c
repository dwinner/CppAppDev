// Concurrent memory access without synchronization

#include <stdio.h>

#ifdef _WIN32
#include <thr/threads.h>
#elif defined unix
#include <threads.h>
#endif

//#include <stdatomic.h>

#define COUNT 10000000L

long counter = 0;
//_Atomic long counter = ATOMIC_VAR_INIT(0L);

void inc_func(void)
{
   for (long i = 0; i < COUNT; ++i)
   {
      ++counter;
   }
}

void dec_func(void)
{
   for (long i = 0; i < COUNT; ++i)
   {
      --counter;
   }
}

int main(void)
{
   const clock_t cl = clock();
   thrd_t th1, th2;

   if (thrd_create(&th1, (thrd_start_t)inc_func, NULL) != thrd_success
      || thrd_create(&th2, (thrd_start_t)dec_func, NULL) != thrd_success)
   {
      fprintf(stderr, "Error creating thread\n");
      return -1;
   }

   thrd_join(th1, NULL);
   thrd_join(th2, NULL);

   printf("Counter: %ld \t", counter);
   printf("CPU time: %ld ms\n", (clock() - cl) * 1000L / CLOCKS_PER_SEC);

   return 0;
}
