/**
 * clock_ex.c : clock() example (clock_t clock( void );)
 */

#include <time.h>
#include <stdio.h>

time_t start, stop;
clock_t ticks;
long count;

int main()
{
   time(&start);

   for (count = 0; count <= 500000000; ++count)
   {
      if (count % 1000000 != 0)
      { continue; }   // measure only full millions
      ticks = clock();
      printf("Performed %ld million integer divisions; "
             "used %0.2f seconds of CPU time.\n", count / 1000000,
             (double) ticks / CLOCKS_PER_SEC);
   }

   time(&stop);
   printf("Finished in about %.0f seconds.\n", difftime(stop, start));

   return 0;
}
