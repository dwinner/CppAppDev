listing 1
max(int a, int b);

int main(void)
{
   int x;

   x = max(10, 20);

  return 0;
}

int max(int a, int b)
{
  return a>b ? a : b;
}

listing 2
/* original code */
x = a + b;
a = a + 1;

listing 3
/* "improved" code -- wrong! */
x = ++a + b;

listing 4
/* This program has an error. */
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  char *p;

  *p = (char *) malloc(100); /* this line is wrong */
  gets(p);
  printf(p);

  return 0;
}

listing 5
/* This program is now correct. */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  char *p;

  p = (char *) malloc(100); /* this is correct */

  if(!p) {
    printf("Out of memory.\n");
    exit(1);
  }

  gets(p);
  printf(p);

  return 0;
}

listing 6
char *myfunc(void);

int main(void)
{
  /* ... */
}

int myfunc(void) /* error reported here */
{
  /* ... */
}

listing 7
/* This program has a syntax error in it. */
#include <stdio.h>

void func1(void);

int main(void)
{
  func1();

  return 0;
}

void func1(void);
{
  printf("This is in func1.\n");
}

listing 8
/* This program will not work. */

int main(void)
{
  int x, num[100];

  for(x=1; x <= 100; ++x) num[x] = x;

  return 0;
}

listing 9
/* This is right. */

int main(void)
{
  int x, num[100];

  for(x=0; x < 100; ++x) num[x] = x;

  return 0;
}

listing 10
#include <stdio.h>

int main(void)
{
  int var1;
  char s[10];
  int var2;

  var1 = 10;  var2 = 10;
  gets(s);
  printf("%s %d %d", s, var1, var2);

  return 0;
}

listing 11
/* This program is wrong. */
#include <stdio.h>

int main(void)
{
  float x, y;

  scanf("%f%f", &x, &y);
  printf("%f", mul(x, y));

  return 0;
}

double mul(float a, float b)
{
  return a*b;
}

listing 12
/* This program is correct. */
#include <stdio.h>

double mul(float a, float b);

int main(void)
{
  float x, y;

  scanf("%f%f", &x, &y);
  printf("%f", mul(x, y));

  return 0;
}

double mul(float a, float b)
{
  return a*b;
}

