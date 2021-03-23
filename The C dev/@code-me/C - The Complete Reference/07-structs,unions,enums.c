listing 1
struct addr
{
  char name[30];
  char street[40];
  char city[20];
  char state[3];
  unsigned long int zip;
};

listing 2
struct addr addr_info;

listing 3
struct addr {
  char name[30];
  char street[40];
  char city[20];
  char state[3];
  unsigned long int zip;
} addr_info, binfo, cinfo;

listing 4
struct {
  char name[30];
  char street[40];
  char city[20];
  char state[3];
  unsigned long int zip;
} addr_info;

listing 5
addr_info.zip = 12345;

listing 6
printf("%d", addr_info.zip);

listing 7
gets(addr_info.name);

listing 8
for(t=0; addr_info.name[t]; ++t)
  putchar(addr_info.name[t]);

listing 9
#include <stdio.h>

int main(void)
{
  struct {
    int a;
    int b;
  } x, y; 

  x.a = 10;

  y = x;  /* assign one structure to another */

  printf("%d", y.a);

  return 0;
}

listing 10
struct addr addr_list[100];

listing 11
printf("%d", addr_list[2].zip);

listing 12
addr_list[2].name[0] = 'X';

listing 13
int main(void)
{
  char choice;

  init_list(); /* initialize the structure array */

  for(;;) {
    choice = menu_select();
    switch(choice) {
      case 1: enter();
        break;
      case 2: delete();
        break;
      case 3: list();
        break;
      case 4: exit(0);
    }
  }

  return 0;
}

listing 14
/* Initialize the list. */
void init_list(void)
{
  register int t;

  for(t=0; t<MAX; ++t) addr_list[t].name[0] = '\0';
}

listing 15
/* Get a menu selection. */
int menu_select(void)
{
  char s[80];
  int c;

  printf("1. Enter a name\n");
  printf("2. Delete a name\n");
  printf("3. List the file\n");
  printf("4. Quit\n");

  do {
    printf("\nEnter your choice: ");
    gets(s);
    c = atoi(s);
  } while(c<0 || c>4);

  return c;
}

listing 16
/* Input addresses into the list. */
void enter(void)
{
  int slot;
  char s[80];

  slot = find_free();
  if(slot==-1) {
    printf("\nList Full");
    return;
  }

  printf("Enter name: ");
  gets(addr_list[slot].name);

  printf("Enter street: ");
  gets(addr_list[slot].street);

  printf("Enter city: ");
  gets(addr_list[slot].city);

  printf("Enter state: ");
  gets(addr_list[slot].state);

  printf("Enter zip: ");
  gets(s);
  addr_list[slot].zip = strtoul(s, '\0', 10);
}

/* Find an unused structure. */
int find_free(void)
{
  register int t;

  for(t=0; addr_list[t].name[0] && t<MAX; ++t) ;

  if(t==MAX) return -1; /* no slots free */
  return t;
}

listing 17
/* Delete an address. */
void delete(void)
{
  register int slot;
  char s[80];

  printf("Enter record #: ");
  gets(s);
  slot = atoi(s);
  if(slot>=0 && slot < MAX)
    addr_list[slot].name[0] = '\0';
}

listing 18
/* Display the list on the screen. */
void list(void)
{
  register int t;

  for(t=0; t<MAX; ++t) {
    if(addr_list[t].name[0]) {
      printf("%s\n", addr_list[t].name);
      printf("%s\n", addr_list[t].street);
      printf("%s\n", addr_list[t].city);
      printf("%s\n", addr_list[t].state);
      printf("%lu\n\n", addr_list[t].zip);
    }
  }
  printf("\n\n");
}

listing 19
/* A simple mailing list example using an array of structures. */
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct addr {
  char name[30];
  char street[40];
  char city[20];
  char state[3];
  unsigned long int zip;
} addr_list[MAX];

void init_list(void), enter(void);
void delete(void), list(void);
int menu_select(void), find_free(void);

int main(void)
{
  char choice;

  init_list(); /* initialize the structure array */
  for(;;) {
    choice = menu_select();
    switch(choice) {
      case 1: enter();
        break;
      case 2: delete();
        break;
      case 3: list();
        break;
      case 4: exit(0);
    }
  }

  return 0;
}

/* Initialize the list. */
void init_list(void)
{
  register int t;

  for(t=0; t<MAX; ++t) addr_list[t].name[0] = '\0';
}

/* Get a menu selection. */
int menu_select(void)
{
  char s[80];
  int c;

  printf("1. Enter a name\n");
  printf("2. Delete a name\n");
  printf("3. List the file\n");
  printf("4. Quit\n");
  do {
    printf("\nEnter your choice: ");
    gets(s);
    c = atoi(s);
  } while(c<0 || c>4);
  return c;
}

/* Input addresses into the list. */
void enter(void)
{
  int slot;
  char s[80];

  slot = find_free();

  if(slot==-1) {
    printf("\nList Full");
    return;
  }

  printf("Enter name: ");
  gets(addr_list[slot].name);

  printf("Enter street: ");
  gets(addr_list[slot].street);

  printf("Enter city: ");
  gets(addr_list[slot].city);

  printf("Enter state: ");
  gets(addr_list[slot].state);

  printf("Enter zip: ");
  gets(s);
  addr_list[slot].zip = strtoul(s, '\0', 10);
}

/* Find an unused structure. */
int find_free(void)
{
  register int t;

  for(t=0; addr_list[t].name[0] && t<MAX; ++t) ;

  if(t==MAX) return -1; /* no slots free */
  return t;
}

/* Delete an address. */
void delete(void)
{
  register int slot;
  char s[80];

  printf("enter record #: ");
  gets(s);
  slot = atoi(s);

  if(slot>=0 && slot < MAX)
    addr_list[slot].name[0] = '\0';
}

/* Display the list on the screen. */
void list(void)
{
  register int t;

  for(t=0; t<MAX; ++t) {
    if(addr_list[t].name[0]) {
      printf("%s\n", addr_list[t].name);
      printf("%s\n", addr_list[t].street);
      printf("%s\n", addr_list[t].city);
      printf("%s\n", addr_list[t].state);
      printf("%lu\n\n", addr_list[t].zip);
    }
  }
  printf("\n\n");
}

listing 20
struct fred
{
  char x;
  int y;
  float z;
  char s[10];
} mike;

listing 21
func(mike.x);    /* passes character value of x */
func2(mike.y);   /* passes integer value of y */
func3(mike.z);   /* passes float value of z */
func4(mike.s);   /* passes address of string s */
func(mike.s[2]); /* passes character value of s[2] */

listing 22
func(&mike.x);    /* passes address of character x */
func2(&mike.y);   /* passes address of integer y */
func3(&mike.z);   /* passes address of float z */
func4(mike.s);    /* passes address of string s */
func(&mike.s[2]); /* passes address of character s[2] */

listing 23
#include <stdio.h>

/* Define a structure type. */
struct struct_type {
  int a, b;
  char ch;
} ;

void f1(struct struct_type parm);

int main(void)
{
  struct struct_type arg;

  arg.a = 1000;

  f1(arg);

  return 0;
}

void f1(struct struct_type parm)
{
  printf("%d", parm.a);
}

listing 24
/* This program is incorrect and will not compile. */
#include <stdio.h>

/* Define a structure type. */
struct struct_type {
  int a, b;
  char ch;
} ;

/* Define a structure similar to struct_type,
   but with a different name. */
struct struct_type2 {
  int a, b;
  char ch;
} ;

void f1(struct struct_type2 parm);

int main(void)
{
  struct struct_type arg;

  arg.a = 1000;

  f1(arg); /* type mismatch */

  return 0;
}

void f1(struct struct_type2 parm)
{
  printf("%d", parm.a);
}

listing 25
struct addr *addr_pointer;

listing 26
struct bal {
  float balance;
  char name[80];
} person;

struct bal *p;  /* declare a structure pointer */

listing 27
p = &person;

listing 28
p->balance

listing 29
/* Display a software timer. */
#include <stdio.h>

#define DELAY 128000

struct my_time {
  int hours;
  int minutes;
  int seconds;
} ;

void display(struct my_time *t);
void update(struct my_time *t);
void delay(void);

int main(void)
{
  struct my_time systime;

  systime.hours = 0;
  systime.minutes = 0;
  systime.seconds = 0;

  for(;;) {
    update(&systime);
    display(&systime);
  }

  return 0;
}

void update(struct my_time *t)
{
  t->seconds++;
  if(t->seconds==60) {
    t->seconds = 0;
    t->minutes++;
  }

  if(t->minutes==60) {
    t->minutes = 0;
    t->hours++;
  }

  if(t->hours==24) t->hours = 0;
  delay();
}

void display(struct my_time *t)
{
  printf("%02d:", t->hours);
  printf("%02d:", t->minutes);
  printf("%02d\n", t->seconds);
}

void delay(void)
{
  long int t;

  /* change this as needed */
  for(t=1; t<DELAY; ++t) ;
}

listing 30
if(t->hours==24) t->hours = 0;

listing 31
struct x {
  int a[10][10]; /* 10 x 10 array of ints */
  float b;
} y;

listing 32
y.a[3][7]

listing 33
struct emp {
  struct addr address; /* nested structure */
  float wage;
} worker;

listing 34
worker.address.zip = 93456;

listing 35
union u_type {
  int i;
  char ch;
};

listing 36
union u_type cnvt;

listing 37
cnvt.i = 10;

listing 38
void func1(union u_type *un)
{
  un->i = 10; /* assign 10 to cnvt through a pointer */
}

listing 39
union pw {
  short int i;
  char ch[2];
};

listing 40
#include <stdio.h>
#include <stdlib.h>

union pw {
  short int i;
  char ch[2];
};

int putw(short int num, FILE *fp);

int main(void)
{
  FILE *fp;

  fp = fopen("test.tmp", "wb+");
  if(fp == NULL) {
    printf("Cannot open file.\n");
    exit(1);
  }

  putw(1025, fp);  /* write the value 1025 */
  fclose(fp);

  return 0;
}

int putw(short int num, FILE *fp)
{
  union pw word;

  word.i = num;

  putc(word.ch[0], fp); /* write first half */
  return putc(word.ch[1], fp); /* write second half */
}


listing 41
struct status_type {
  unsigned delta_cts: 1;
  unsigned delta_dsr: 1;
  unsigned tr_edge:   1;
  unsigned delta_rec: 1;
  unsigned cts:       1;
  unsigned dsr:       1;
  unsigned ring:      1;
  unsigned rec_line:  1;
} status;

listing 42
status = get_port_status();
if(status.cts) printf("clear to send");
if(status.dsr) printf("data ready");

listing 43
status.ring = 0;

listing 44
struct status_type {
  unsigned :    4;
  unsigned cts: 1;
  unsigned dsr: 1;
} status;

listing 45
struct emp {
  struct addr address;
  float pay;
  unsigned lay_off:    1; /* lay off or active */
  unsigned hourly:     1; /* hourly pay or wage */
  unsigned deductions: 3; /* IRS deductions */
};

listing 46
enum coin { penny, nickel, dime, quarter,
            half_dollar, dollar};

listing 47
enum coin money;

listing 48
money = dime;
if(money==quarter) printf("Money is a quarter.\n");

listing 49
printf("%d %d", penny, dime);

listing 50
enum coin { penny, nickel, dime, quarter=100,
            half_dollar, dollar};

listing 51
/* this will not work */
money = dollar;
printf("%s", money);

listing 52
/* this code is wrong */
strcpy(money, "dime");

listing 53
switch(money) {
  case penny: printf("penny");
    break;
  case nickel: printf("nickel");
    break;
  case dime: printf("dime");
    break;
  case quarter: printf("quarter");
    break;
  case half_dollar: printf("half_dollar");
    break;
  case dollar: printf("dollar");
}

listing 54
char name[][12]={
  "penny",
  "nickel",
  "dime",
  "quarter",
  "half_dollar",
  "dollar"
};
printf("%s", name[money]);

listing 55
struct MyStruct {
  int a;
  int b;
} ;

listing 56
struct MyStruct obj;

listing 57
MyStruct obj; /* OK for C++, wrong for C */

listing 58
char ch;
int i;
double f;

printf("%d", sizeof(ch));
printf("%d", sizeof(i));
printf("%d", sizeof(f));

listing 59
struct s {
  char ch;
  int i;
  double f;
} s_var;

listing 60
struct s *p;
p = malloc(sizeof(struct s));

listing 61
union u {
  char ch;
  int i;
  double f;
} u_var;

listing 62
typedef float balance;

listing 63
balance over_due;

listing 64
typedef balance overdraft;

