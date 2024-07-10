// mtx_timedlock_ex.c : mtx_timedlock() example
// -------------------------------------------------------------

#include <threads.h>   // int mtx_timedlock( mtx_t *restrict mtx,
//                    const struct timespec *restrict ts);
#include <stdio.h>
#include <time.h>
#include <stdint.h>

mtx_t mtx;

int func(void *thrd);                   // Thread function.

int main()
{
   thrd_t th;
   if (mtx_init(&mtx, mtx_timed) != thrd_success)
   {
      fputs("Initialization error.\n", stderr);
      return 1;
   }

   mtx_lock(&mtx);                      // Lock the mutex.
   if (thrd_create(&th, func, "Thread A") != thrd_success)
   {
      fputs("Thread error.\n", stderr);
      return 2;
   }

   thrd_join(th, NULL);
   mtx_destroy(&mtx);
   return 0;
}

int func(void *thrd)
{
   struct timespec ts;
   timespec_get(&ts, TIME_UTC);        // The current time;
   ts.tv_sec += 3;                      // 3 seconds from now.

   printf("%s waiting ...\n", (char *) thrd);
   int res = mtx_timedlock(&mtx, &ts);
   switch (res)
   {
      case thrd_success:
         puts("Obtained mutex\n... releasing ...");
         mtx_unlock(&mtx);
         break;
      case thrd_timedout:
         puts("Timed out.");
         break;
      default:
         puts("mtx_timedlock: error.");
   };
   return res;
}
