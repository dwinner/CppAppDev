// cnd_broadcast_ex.c : cnd_broadcast() example
//
// Wake up three threads waiting for one condition variable using
// cnd_signal() and cnd_broadcast().
// -------------------------------------------------------------

#include <threads.h>   // int cnd_broadcast(cnd_t *cond);
#include <stdatomic.h>
#include <stdio.h>

cnd_t cv;
mtx_t mtx;               // Mutex for the condition variable cv
atomic_bool go = ATOMIC_VAR_INIT(0);       // Initially false

int th_func(void *arg)                    // Thread function
{
   mtx_lock(&mtx);
   printf("%s waiting ... \n", (char *) arg);

   while (!go)
   {
      if (cnd_wait(&cv, &mtx) != thrd_success)
      {
         return -1;
      }
   }

   printf("%s finished.\n", (char *) arg);
   mtx_unlock(&mtx);
   return 0;
}

int main(void)
{
   thrd_t th1, th2, th3;

   if (cnd_init(&cv) != thrd_success
       || mtx_init(&mtx, mtx_plain) != thrd_success)
   {
      fputs("Initialization error.\n", stderr);
      return 1;
   }

   if (thrd_create(&th1, th_func, "Thread 1") != thrd_success
       || thrd_create(&th2, th_func, "Thread 2") != thrd_success
       || thrd_create(&th3, th_func, "Thread 3") != thrd_success)
   {
      fputs("Thread error.\n", stderr);
      return 2;
   }

   struct timespec duration = {.tv_sec = 1};
   thrd_sleep(&duration, NULL);       // Wait 1 second.

   go = 1;
   puts("cnd_signal ...");
   if (cnd_signal(&cv) != thrd_success)
   {
      fputs("Signal error.\n", stderr);
      return 3;
   }

   thrd_sleep(&duration, NULL);       // Wait 1 second.
   puts("cnd_broadcast ...");
   if (cnd_broadcast(&cv) != thrd_success)
   {
      fputs("Broadcast error.\n", stderr);
      return 4;
   }

   thrd_join(th1, NULL);
   thrd_join(th2, NULL);
   thrd_join(th3, NULL);

   cnd_destroy(&cv);
   mtx_destroy(&mtx);
   return 0;
}
