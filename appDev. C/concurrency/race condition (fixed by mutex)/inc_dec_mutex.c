// Adding a mutex to the program to fix race condition

#include <stdio.h>
#include <threads.h>

#define COUNT 10000000L

long counter = 0;
mtx_t mtx; // A mutex for access to counter

void inc_func(void)
{
   for (long i = 0; i < COUNT; ++i)
   {
      mtx_lock(&mtx);
      ++counter;
      mtx_unlock(&mtx);
   }
}

void dec_func(void)
{
   for (long i = 0; i < COUNT; ++i)
   {
      mtx_lock(&mtx);
      --counter;
      mtx_unlock(&mtx);
   }
}

int main(void)
{
   if (mtx_init(&mtx, mtx_plain) != thrd_success)
   {
      fprintf(stderr, "Error initializing the mutex.\n");
      return -1;
   }

   // start threads, wait for them to finish, print output:
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

   mtx_destroy(&mtx);
   return 0;
}
