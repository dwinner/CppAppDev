listing 1
#include <time.h>
#include <stdio.h>

int main(void)
{
  struct tm *ptr;
  time_t lt;

  lt = time(NULL);
  ptr = localtime(&lt);
  printf(asctime(ptr));

  return 0;
}

listing 2
void elapsed_time(void)
{
  printf("Elapsed time: %u secs.\n", clock()/CLOCKS_PER_SEC);
}

listing 3
#include <time.h>
#include <stdio.h>

int main(void)
{
  time_t lt;

  lt = time(NULL);
  printf(ctime(&lt));

  return 0;
}

listing 4
#include <time.h>
#include <stdio.h>

int main(void)
{
  time_t start,end;
  volatile long unsigned t;

  start = time(NULL);
  for(t=0; t<5000000; t++) ;
  end = time(NULL);
  printf("Loop used %f seconds.\n", difftime(end, start));

  return 0;
}

listing 5
#include <time.h>
#include <stdio.h>

/* Print local and UTC time. */
int main(void)
{
  struct tm *local, *gm;
  time_t t;

  t = time(NULL);
  local = localtime(&t);
  printf("Local time and date: %s\n", asctime(local));
  gm = gmtime(&t);
  printf("Coordinated Universal Time and date: %s", asctime(gm));

  return 0;
}

listing 6
#include <stdio.h>
#include <locale.h>

int main(void)
{
  struct lconv lc;

  lc = *localeconv();

  printf("Decimal symbol is: %s\n", lc.decimal_point);

  return 0;
}

listing 7
#include <time.h>
#include <stdio.h>

/* Print local and UTC time. */
int main(void)
{
  struct tm *local;
  time_t t;

  t = time(NULL);
  local = localtime(&t);
  printf("Local time and date: %s\n", asctime(local));
  local = gmtime(&t);
  printf("UTC time and date: %s\n", asctime(local));

  return 0;
}

listing 8
#include <time.h>
#include <stdio.h>

int main(void)
{
  struct tm t;
  time_t t_of_day;

  t.tm_year = 2005-1900;
  t.tm_mon = 0;
  t.tm_mday = 3;
  t.tm_hour = 0;  /* hour, min, sec don't matter */
  t.tm_min = 0;   /* as long as they don't cause a */
  t.tm_sec = 1;   /* new day to occur */
  t.tm_isdst = 0;

  t_of_day = mktime(&t);
  printf(ctime(&t_of_day));

  return 0;
}

listing 9
#include <locale.h>
#include <stdio.h>

int main(void)
{
  printf(setlocale(LC_ALL, ""));

  return 0;
}

listing 10
#include <time.h>
#include <stdio.h>

int main(void)
{
  struct tm *ptr;
  time_t lt;
  char str[80];

  lt = time(NULL);
  ptr = localtime(&lt);

  strftime(str, 100, "It is now %H %p.", ptr);
  printf(str);

  return 0;
}

listing 11
#include <time.h>
#include <stdio.h>

int main(void)
{
  struct tm *ptr;
  time_t lt;

  lt = time(NULL);
  ptr = localtime(&lt);
  printf(asctime(ptr));

  return 0;
}

