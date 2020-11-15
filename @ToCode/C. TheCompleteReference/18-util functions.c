listing 1
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  for(;;)
    if(getchar()=='A') abort();

  return 0;
}

listing 2
int get_abs(void)
{
  char num[80];

  gets(num);
  return abs(atoi(num));
}

listing 3
/* ... */
ch = read_port();
assert(!(ch & 128)); /* check bit 7 */

listing 4
#include <stdlib.h>
#include <stdio.h>

void done(void);

int main(void)
{
  if(atexit(done)) printf("Error in atexit().");

  return 0;
}

void done(void)
{
  printf("Hello There");
}

listing 5
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  char num1[80], num2[80];

  printf("Enter first: ");
  gets(num1);
  printf("Enter second: ");
  gets(num2);
  printf("The sum is: %lf.", atof(num1) + atof(num2));

  return 0;
}

listing 6
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  char num1[80], num2[80];

  printf("Enter first: ");
  gets(num1);
  printf("Enter second: ");
  gets(num2);
  printf("The sum is: %d.", atoi(num1)+atoi(num2));

  return 0;
}

listing 7
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  char num1[80], num2[80];

  printf("Enter first: ");
  gets(num1);
  printf("Enter second: ");
  gets(num2);
  printf("The sum is: %ld.", atol(num1)+atol(num2));

  return 0;
}

listing 8
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

char *alpha = "abcdefghijklmnopqrstuvwxyz";

int comp(const void *ch, const void *s);

int main(void)
{
  char ch;
  char *p;

  printf("Enter a character: ");
  ch = getchar();
  ch = tolower(ch);
  p = (char *) bsearch(&ch, alpha, 26, 1, comp);
  if(p) printf(" %c is in alphabet\n", *p);
  else printf("is not in alphabet\n");

  return 0;
}

/* Compare two characters. */
int comp(const void *ch, const void *s)
{
  return *(char *)ch - *(char *)s;
}

listing 9
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  div_t n;

  n = div(10, 3);

  printf("Quotient and remainder: %d %d.\n", n.quot, n.rem);

  return 0;
}

listing 10
int menu(void)
{
  char choice;

  do {
    printf("Enter names (E)\n");
    printf("Delete name (D)\n");
    printf("Print (P)\n");
    printf("Quit (Q)\n");
    choice = getchar();
  } while(!strchr("EDPQ", toupper(choice)));

  if(choice=='Q') exit(0);

  return choice;
}

listing 11
char *p
/* ... (/
p = getevn("DEVICES");

listing 12
long int get_labs()
{
  char num[80];

  gets(num);

  return labs(atol(num));
}

listing 13
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  ldiv_t n;

  n = ldiv(10L, 3L);

  printf("Quotient and remainder: %ld %ld.\n", n.quot, n.rem);

  return 0;
}

listing 14
#include <setjmp.h>
#include <stdio.h>

jmp_buf ebuf;
void f2(void);

int main(void)
{
  int i;

  printf("1 ");
  i = setjmp(ebuf);
  if(i == 0) {
    f2();
    printf("This will not be printed.");
  }
  printf("%d", i);

  return 0;
}

void f2(void)
{
  printf("2 ");
  longjmp(ebuf, 3);
}

listing 15a
printf("%d", mblen(mb, 2));

listing 16b
mbstowcs(str, mb, 4);

listing 17c
mbtowc(widenorm, mbstr, 2);

listing 18
#include <stdlib.h>
#include <stdio.h>

int num[10] = {
  1, 3, 6, 5, 8, 7, 9, 6, 2, 0
};

int comp(const void *, const void *);

int main(void)
{
  int i;

  printf("Original array: ");
  for(i=0; i<10; i++) printf("%d ", num[i]);

  qsort(num, 10, sizeof(int), comp);

  printf("Sorted array: ");
  for(i=0; i<10; i++) printf("%d ", num[i]);

  return 0;
}

/* compare the integers */
int comp(const void *i, const void *j)
{
  return *(int *)i - *(int *)j;
}

listing 19
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  int i;

  for(i=0; i<10; i++)
    printf("%d ", rand());

  return 0;
}

listing 20
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Seed rand() with the system time
   and display the first 10 numbers.
*/
int main(void)
{
  int i, stime;
  long ltime;

  /* get the current calendar time */
  ltime = time(NULL);
  stime = (unsigned) ltime/2;
  srand(stime);

  for(i=0; i<10; i++) printf("%d ", rand());

  return 0;
}

listing 21
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
  char *end, *start = "100.00 pliers 200.00 hammers";

  end = start;
  while(*start) {
    printf("%f, ", strtod(start, &end));
    printf("Remainder: %s\n" ,end);
    start = end;
    /* move past the non-digits */
    while(!isdigit(*start) && *start) start++;
  }

  return 0;
}

listing 22
long int read_long(void)
{
  char start[80], *end;

  printf("Enter a number: ");
  gets(start);
  return strtol(start, &end, 10);
}

listing 23
unsigned long int read_unsigned_long(void)
{
  char start[80], *end;

  printf("Enter a hex number: ");
  gets(start);
  return strtoul(start, &end, 16);
}

listing 24
#include <stdlib.h>

int main(void)
{
  return system("dir");
}

listing 25
#include <stdio.h>
#include <stdarg.h>

double sum_series(int num, ...);

/* Variable length argument example - sum a series. */
int main(void)
{
  double d;

  d = sum_series(5, 0.5, 0.25, 0.125, 0.0625, 0.03125);

  printf("Sum of series is %f.\n", d);

  return 0;
}

double sum_series(int num, ...)
{
  double sum=0.0, t;
  va_list argptr;

  /* initialize argptr */
  va_start(argptr, num);

  /* sum the series */
  for( ; num; num--) {
    t = va_arg(argptr, double); /* get next argument */
    sum += t;
  }

  /* do orderly shutdown */
  va_end(argptr);
  return sum;
}

