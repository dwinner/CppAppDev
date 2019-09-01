listing 1
#include <stdio.h>

inline int max(int a, int b)
{
  return a > b ? a : b;
}

int main(void)
{
  int x=5, y=10;

  printf("Max of %d and %d is: %d\n", x, y, max(x, y));

  return 0;
}

listing 2
#include <stdio.h>

int main(void)
{
  int x=5, y=10;

  printf("Max of %d and %d is: %d\n", x, y, (x>y ? x : y));

  return 0;
}

listing 3
#include <stdio.h>

int main(void)
{
  int i;

  i = 10;

  int j; // wrong for C89; OK for C99 and C++

  j = i;

  printf("%d %d", i, j);

  return 0;
}

listing 4
#include <stdio.h>

int main(void)
{
  // declare i within for
  for(int i=0; i < 10; i++)
    printf("%d ", i);

  return 0;
}

listing 5
#include <stdio.h>

int main(void)
{
  int i = -99;

  // declare i within for
  for(int i=0; i < 10; i++)
    printf("%d ", i);

  printf("\n");
 
  printf("Value of i is: %d", i); // displays -99

  return 0;
}

listing 6
void StrUpper(char *str)
{
  static int i = 0;
  
  i++;
  printf("%s has been called %d time(s).\n", __func__, i);
  
  while(*str) {
    *str = toupper(*str);
    str++;
  }
}

listing 7
int isEven(int val)
{
  return !(val%2);
}

listing 8
/* use integer default */
isEven(int val) 
{
  return !(val%2);
}

listing 9
isEven(const val) 
{
  return !(val%2);
}

