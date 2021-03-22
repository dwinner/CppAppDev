/**
 * cnd_timedwait_ex.c : cnd_timedwait() example:
 * Wake up three threads waiting for one condition variable using cnd_signal() and cnd_broadcast().
 * int cnd_timedwait(cnd_t *restrict cond, mtx_t *restrict mtx, const struct timespec *restrict ts);
 */

#include <thread>
#include <atomic>
#include <cstdio>

std::cnd_t cv;
std::mtx_t mtx;               // Mutex for the condition variable cv
std::atomic_bool go = ATOMIC_VAR_INIT(0);        // Initially false.

int th_func(void *millisec)                 // Thread function.
{
   int res = thrd_success;
   struct timespec ts;
   timespec_get(&ts, TIME_UTC);            // The current time
   ts.tv_nsec += *(long *)millisec *1E6;   // + millions of ns.

   mtx_lock(&mtx);
   puts("Waiting ...");
   while (!go && res == thrd_success)
      res = cnd_timedwait(&cv, &mtx, &ts);
   switch (res)
   {
      case thrd_success:
         puts("Working ... done.");
         break;
      case thrd_timedout:
         puts("Timed out.");
         break;
      default:
         puts("cnd_timedwait: error.");
   };
   mtx_unlock(&mtx);
   return res;
}

int main(void)
{
   thrd_t th1, th2;
   long tm_limit1 = 100, tm_limit2 = 500;      // In milliseconds.

   if (cnd_init(&cv) != thrd_success
       || mtx_init(&mtx, mtx_plain) != thrd_success)
   {
      fputs("Initialization error.\n", stderr);  return 1;
   }

   if (   thrd_create( &th1, th_func, &tm_limit1) != thrd_success
          || thrd_create( &th2, th_func, &tm_limit2) != thrd_success)
   {
      fputs("Thread error.\n", stderr);   return 2;
   }

   struct timespec duration = { 0 };
   duration.tv_nsec = 300 * 1E6;               // 300 million nanoseconds.
   thrd_sleep(&duration, NULL);                // Wait 200 milliseconds.
   go = 1;

   puts("Sending broadcast ...");
   cnd_broadcast(&cv);

   thrd_join(th1, NULL);  thrd_join(th2, NULL);
   cnd_destroy(&cv);
   mtx_destroy(&mtx);

   return 0;
}
