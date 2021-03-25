// timespec_get_ex.c : timespec_get() example
// -------------------------------------------------------------
// int timespec_get(struct timespec *ts, int base);

#include <time.h>
#include <stdio.h>

int main()
{
   struct timespec ts;

   if (timespec_get(&ts, TIME_UTC) != 0)
   {
      printf("The exact local time:\n"
             "%.24s and %09lu nanoseconds\n", ctime(&ts.tv_sec), ts.tv_nsec);
   }

   return 0;
}
