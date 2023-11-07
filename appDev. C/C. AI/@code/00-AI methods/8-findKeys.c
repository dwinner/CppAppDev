/*********************************************************************
 *         Find the keys                                             *
 *********************************************************************/
/* Find the keys using a depth-first search. */
#include <stdio.h>
#include <string.h>

#define MAX 100

/* structure of the keys database */
struct FL {
  char from[20];
  char to[20];
  char skip;
};

struct FL keys[MAX];  /* array of db structures */

int f_pos = 0;    /* number of rooms in house */
int find_pos = 0; /* index for searching keys db */

int tos = 0;      /* top of stack */
struct stack {
  char from[20];
  char to[20];
} ;
struct stack bt_stack[MAX]; /* backtrack stack */

void setup(void), route(void);
void assert_keys(char *from, char *to);
void push(char *from, char *to);
void pop(char *from, char *to);
void iskeys(char *from, char *to);
int find(char *from, char *anywhere);
int match(char *from, char *to);

int main(void)
{
  char from[20] = "front_door";
  char to[20] = "keys";

  setup();
  iskeys(from, to);
  route();

  return 0;
}

/* Initialize the database. */
void setup(void)
{
  assert_keys("front_door", "lr");
  assert_keys("lr", "bath");
  assert_keys("lr", "hall");
  assert_keys("hall", "bd1");
  assert_keys("hall", "bd2");
  assert_keys("hall", "mb");
  assert_keys("lr", "kitchen");
  assert_keys("kitchen", "keys");
}

/* Put facts into the database. */
void assert_keys(char *from, char *to)
{
  if(f_pos < MAX) {
    strcpy(keys[f_pos].from, from);
    strcpy(keys[f_pos].to, to);
    keys[f_pos].skip = 0;
    f_pos++;
  }
  else printf("Keys database full.\n");
}

/* Show the route to the keys. */
void route(void)
{
  int t;

  t = 0;
  while(t < tos) {
    printf("%s", bt_stack[t].from);
    t++;
    if(t < tos) printf(" to ");
  }
  printf("\n");
}

/* See if there is a match. */
int match(char *from, char *to)
{
  register int t;

  for(t=f_pos-1; t > -1; t--)
    if(!strcmp(keys[t].from, from) &&
      !strcmp(keys[t].to, to)) return 1;

  return 0;  /* not found */
}

/* Given from, find anywhere. */
int find(char *from, char *anywhere)
{ 
  find_pos = 0;

  while(find_pos < f_pos) {
    if(!strcmp(keys[find_pos].from, from) &&
      !keys[find_pos].skip) {
        strcpy(anywhere, keys[find_pos].to);
        keys[find_pos].skip = 1;
        return 1;
    }
    find_pos++;
  }
  return 0;
}

/* Determine if there is a route between from and to. */
void iskeys(char *from, char *to)
{
  char anywhere[20];

  if(match(from, to)) {
    push(from, to); /* distance */
    return;
  }

  if(find(from, anywhere)) {
    push(from, to);
    iskeys(anywhere, to);
  }
  else if(tos > 0) {
    pop(from, to);
    iskeys(from, to);
  }
}

/* Stack Routines */
void push(char *from, char *to)
{
  if(tos < MAX) {
    strcpy(bt_stack[tos].from, from);
    strcpy(bt_stack[tos].to, to);
    tos++;
  }
  else printf("Stack full.\n");
}

void pop(char *from, char *to)
{
  if(tos > 0) {
    tos--;
    strcpy(from, bt_stack[tos].from);
    strcpy(to, bt_stack[tos].to);
  }
  else printf("Stack underflow.\n");
}

