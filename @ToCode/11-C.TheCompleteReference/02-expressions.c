listing 1
int i,j,l;
short int si;
unsigned int ui;
double balance, profit, loss;

listing 2
void func1(void)
{
  int x;

  x = 10;
}

void func2(void)
{
  int x;

  x = -199;
}

listing 3
void f(void)
{
  int t; 

  scanf("%d%*c", &t); 

  if(t==1) {
    char s[80];  /* this is created only upon
                    entry into this block */
    printf("Enter name:");
    gets(s);
    /* do something ... */
  }

  /* s not known here */
}

listing 4
#include <stdio.h>

int main(void)
{
  int x;

  x = 10;

  if(x == 10) {
    int x; /* this x hides the outer x */

    x = 99;
    printf("Inner x: %d\n", x);
  }

  printf("Outer x: %d\n", x);

  return 0;
}

listing 5
/* This function is in error if compiled as
   a C89 program.
*/
void f(void)
{
  int i;

  i = 10;

  int j;  /* this line will cause an error */

  j = 20;
}

listing 6
#include <stdio.h>

void f(void); 

int main(void)
{
  int i; 

  for(i=0; i<10; i++)  f();

  return 0;
}

void f(void)
{
  int j = 10;

  printf("%d ", j);

  j++;  /* this line has no lasting effect */
}

listing 7
/* Return 1 if c is part of string s; 0 otherwise */
int is_in(char *s, char c)
{
  while(*s)
    if(*s==c) return 1;
    else s++;

  return 0;
}

listing 8
#include <stdio.h>
int count;  /* count is global  */

void func1(void);
void func2(void);

int main(void)
{
  count = 100;
  func1();

  return 0;
}

void func1(void) 
{
  int temp;

  temp = count;
  func2();
  printf("count is %d", count); /* will print 100 */
}

void func2(void)
{
  int count;

  for(count=1; count<10; count++)
    putchar('.');
}

listing 9
const int a=10;

listing 10
#include <stdio.h>

void sp_to_dash(const char *str);

int main(void)
{
  sp_to_dash("this is a test");

  return 0;
}

void sp_to_dash(const char *str)
{
  while(*str) {
    if(*str== ' ') printf("%c", '-');
    else printf("%c", *str);
    str++;
  }
}

listing 11
/* This is wrong. */
void sp_to_dash(const char *str)
{
  while(*str) {
    if(*str==' ' ) *str = '-'; /* can't do this; str is const */
    printf("%c", *str);
    str++;
  }
}

listing 12
const volatile char *port = (const volatile char *) 0x30;

listing 13
#include <stdio.h>

int main(void)
{
  extern int first, last; /* use global vars */

  printf("%d %d", first, last);

  return 0;
}

/* global definition of first and last */
int first = 10, last = 20;

listing 14
int series(void)
{
  static int series_num;

  series_num = series_num+23;
  return series_num;
} 

listing 15
int series(void)
{
  static int series_num = 100;

  series_num = series_num+23;
  return series_num;
}

listing 16
/* This must all be in one file - preferably by itself. */

static int series_num;
void series_start(int seed);
int series(void);

int series(void)
{
  series_num = series_num+23;
  return series_num;
}

/* initialize series_num */
void series_start(int seed)
{
  series_num = seed;
}

listing 17
int int_pwr(register int m,  register int e)
{
  register int temp;

  temp = 1;

  for(; e; e--) temp = temp * m;
  return temp;
}

listing 18
char ch = 'a';
int first = 0;
double balance = 123.23;

listing 19
wchar_t wc;
wc = L'A';

listing 20
int hex = 0x80;   /* 128 in decimal */
int oct = 012;    /* 10 in decimal */

listing 21
#include <stdio.h>

int main(void)
{
  printf("\n\tThis is a test.");

  return 0;
}

listing 22
int x;
char ch;
float  f;

void func(void)
{
  ch = x;    /* line 1 */
  x = f;     /* line 2 */
  f = ch;    /* line 3 */
  f = x;     /* line 4 */
}

listing 23
x = y = z = 0;

listing 24
x = x+10; 

listing 25
x += 10;

listing 26
x = x-100; 

listing 27
x -= 100;

listing 28
int x, y;

x = 5;
y = 2;

printf("%d ", x/y);   /* will display 2 */
printf("%d ", x%y);   /* will display 1, the remainder of
                         the integer division */

x = 1;
y = 2;

printf("%d %d", x/y, x%y); /*  will display 0 1 */

listing 29
x = x+1;

listing 30
++x; 

listing 31
x = x-1;

listing 32
x--;

listing 33
x = x+1;

listing 34
++x;

listing 36
x = 10;
y = ++x;

listing 37
x = 10;
y = x++;

listing 38
#include <stdio.h>

int xor(int a, int b);

int main(void)
{
  printf("%d", xor(1, 0));
  printf("%d", xor(1, 1));
  printf("%d", xor(0, 1));
  printf("%d", xor(0, 0));

  return 0;
}

/* Perform a logical XOR operation using the
   two arguments. */
int xor(int a, int b)
{
  return (a || b) && !(a && b);
}

listing 39
int x; 

x = 100;
printf("%d", x>10);

listing 40
char get_char_from_modem(void)
{
  char ch;

  ch = read_modem(); /* get a character from the
                        modem port */
  return(ch & 127);
}

listing 41
/* A bit shift example. */
#include <stdio.h>

int main(void)
{
  unsigned int i;
  int j;

  i = 1;

  /* left shifts */
  for(j=0; j<4; j++) {
    i = i << 1;  /* left shift i by 1, which
                    is same as a multiply by 2 */
    printf("Left shift %d: %d\n", j, i);
  }

  /* right shifts */
  for(j=0; j<4; j++) {
    i = i >> 1;  /* right shift i by 1, which
                    is same as a division by 2 */
    printf("Right shift %d: %d\n", j, i);
  }

  return 0;
}

listing 42
/* A simple cipher function. */
char encode(char ch)
{
  return(~ch); /* complement it */
}

listing 43
x = 10;

y = x>9 ? 100 : 200;

listing 44
x = 10;

if(x>9) y = 100;
else y = 200;

listing 45
m = &count;

listing 46
q = *m; 

listing 47
char *ch;

listing 48
int x, *y, count;

listing 49
#include <stdio.h>

int main(void)
{
  int target, source;
  int *m;

  source = 10;
  m = &source;
  target = *m;

  printf("%d", target);

  return 0;
}

listing 50
double f;

printf("%d ", sizeof f);
printf("%d", sizeof(int));

listing 51
/* Write 6 integers to a disk file. */
void put_rec(int rec[6], FILE *fp)
{
  int len; 

  len = fwrite(rec, sizeof(int)*6, 1, fp);
  if(len != 1) printf("Write Error");
}

listing 52
x = (y=3, y+1);

listing 53
struct employee
{
  char name[80];
  int age;
  float wage;
} emp; 

struct employee *p = &emp; /* address of emp into p */

listing 54
emp.wage = 123.23;

listing 55
p->wage = 123.23;

listing 56
#include <stdio.h>
char s[80];

int main(void)
{
  s[3] = 'X';
  printf("%c", s[3]);

  return 0;
} 

listing 57
x = f1() + f2();

listing 58
(float) x/2

listing 59
#include <stdio.h>

int main(void) /* print i and i/2 with fractions */
{
  int i;

  for(i=1; i<=100; ++i)
    printf("%d / 2 is: %f\n", i, (float) i /2);

  return 0;
}

listing 60
x=10/y~(127/x);

x = 10 / y ~(127/x);

listing 61
x = y/3-34*temp+127;

x = (y/3) - (34*temp) + 127;

