listing 1
#define MAX 100

/* structure of the flight database */
struct FL {
  char from[20];
  char to[20];
  int distance;
  char skip;  /* used in backtracking */
};

struct FL flight[MAX];  /* array of db structures */

int f_pos = 0;    /* number of entries in flight db */
int find_pos = 0; /* index for searching flight db */

listing 2
void setup(void)
{
  assert_flight("New York", "Chicago", 1000);
  assert_flight("Chicago", "Denver", 1000);
  assert_flight("New York", "Toronto", 800);
  assert_flight("New York", "Denver", 1900);
  assert_flight("Toronto", "Calgary", 1500);
  assert_flight("Toronto", "Los Angeles", 1800);
  assert_flight("Toronto", "Chicago", 500);
  assert_flight("Denver", "Urbana", 1000);
  assert_flight("Denver", "Houston", 1500);
  assert_flight("Houston", "Los Angeles", 1500);
  assert_flight("Denver", "Los Angeles", 1000);
}

/* Put facts into the database. */
void assert_flight(char *from, char *to, int dist)
{
  if(f_pos < MAX) {
    strcpy(flight[f_pos].from, from);
    strcpy(flight[f_pos].to, to);
    flight[f_pos].distance = dist;
    flight[f_pos].skip = 0;
    f_pos++;
  }
  else printf("Flight database full.\n");
}

listing 3
/* If flight between from and to, then return
   the distance of flight; otherwise, return 0. */
int match(char *from, char *to)
{
  register int t;

  for(t=f_pos-1; t > -1; t--)
    if(!strcmp(flight[t].from, from) &&
      !strcmp(flight[t].to, to)) return flight[t].distance;

  return 0;  /* not found */
}

listing 4
/* Given from, find anywhere. */
int find(char *from, char *anywhere)
{
  find_pos = 0;
  while(find_pos < f_pos) {
    if(!strcmp(flight[find_pos].from, from) &&
      !flight[find_pos].skip) {
        strcpy(anywhere, flight[find_pos].to);
        flight[find_pos].skip = 1; /* make active */
        return flight[find_pos].distance;
    }
    find_pos++;
  }
  return 0;
}

listing 5
/* Stack Routines */
void push(char *from, char *to, int dist)
{
  if(tos < MAX) {
    strcpy(bt_stack[tos].from, from);
    strcpy(bt_stack[tos].to, to);
    bt_stack[tos].dist = dist;
    tos++;
  }
  else printf("Stack full.\n");
}

void pop(char *from, char *to, int *dist)
{
  if(tos > 0) {
    tos--;
    strcpy(from, bt_stack[tos].from);
    strcpy(to, bt_stack[tos].to);
    *dist = bt_stack[tos].dist;
  }
  else printf("Stack underflow.\n");
}

listing 6
/* Determine if there is a route between from and to. */
void isflight(char *from, char *to)
{
  int d, dist;
  char anywhere[20];

  /* see if at destination */
  if(d=match(from, to)) {
    push(from, to, d);
    return;
  }

  /* try another connection */
  if(dist=find(from, anywhere)) {
    push(from, to, dist);
    isflight(anywhere, to);
  }
  else if(tos > 0) {
    /* backtrack */
    pop(from, to, &dist);
    isflight(from, to);
  }
}

listing 7
/* Show the route and total distance. */
void route(char *to)
{
  int dist, t;

  dist = 0;
  t = 0;
  while(t < tos) {
    printf("%s to ", bt_stack[t].from);
    dist += bt_stack[t].dist;
    t++;
  }
  printf("%s\n", to);
  printf("Distance is %d.\n", dist);
}

listing 8
/* Depth-first search. */
#include <stdio.h>
#include <string.h>

 #define MAX 100

/* structure of the flight database */
struct FL {
  char from[20];
  char to[20];
  int distance;
  char skip; /* used in backtracking */
};

struct FL flight[MAX]; /* array of db structures */

int f_pos = 0;    /* number of entries in flight db */
int find_pos = 0; /* index for searching flight db */
int tos = 0;      /* top of stack */
struct stack {
  char from[20];
  char to[20];
  int dist;
} ;
struct stack bt_stack[MAX]; /* backtrack stack */

void setup(void), route(char *to);
void assert_flight(char *from, char *to, int dist);
void push(char *from, char *to, int dist);
void pop(char *from, char *to, int *dist);
void isflight(char *from, char *to);
int find(char *from, char *anywhere);
int match(char *from, char *to);

int main(void)
{
  char from[20], to[20];

  setup();

  printf("From? ");
  gets(from);
  printf("To? ");
  gets(to);

  isflight(from,to);
  route(to);

  return 0;
}

/* Initialize the flight database. */
void setup(void)
{
  assert_flight("New York", "Chicago", 1000);
  assert_flight("Chicago", "Denver", 1000);
  assert_flight("New York", "Toronto", 800);
  assert_flight("New York", "Denver", 1900);
  assert_flight("Toronto", "Calgary", 1500);
  assert_flight("Toronto", "Los Angeles", 1800);
  assert_flight("Toronto", "Chicago", 500);
  assert_flight("Denver", "Urbana", 1000);
  assert_flight("Denver", "Houston", 1500);
  assert_flight("Houston", "Los Angeles", 1500);
  assert_flight("Denver", "Los Angeles", 1000);
}

/* Put facts into the database. */
void assert_flight(char *from, char *to, int dist)
{

  if(f_pos < MAX) {
    strcpy(flight[f_pos].from, from);
    strcpy(flight[f_pos].to, to);
    flight[f_pos].distance = dist;
    flight[f_pos].skip = 0;
    f_pos++;
  }
  else printf("Flight database full.\n");
}

/* Show the route and total distance. */
void route(char *to)

{
  int dist, t;

  dist = 0;
  t = 0;
  while(t < tos) {
    printf("%s to ", bt_stack[t].from);
    dist += bt_stack[t].dist;
    t++;
  }
  printf("%s\n", to);
  printf("Distance is %d.\n", dist);
}

/* If flight between from and to, then return
   the distance of flight; otherwise, return 0. */
int match(char *from, char *to)
{
  register int t;

  for(t=f_pos-1; t > -1; t--)
    if(!strcmp(flight[t].from, from) &&
      !strcmp(flight[t].to, to)) return flight[t].distance;

  return 0; /* not found */
}

/* Given from, find anywhere. */
int find(char *from, char *anywhere)
{
  find_pos = 0;
  while(find_pos < f_pos) {
    if(!strcmp(flight[find_pos].from,from) &&
      !flight[find_pos].skip) {
        strcpy(anywhere,flight[find_pos].to);
        flight[find_pos].skip = 1; /* make active */
        return flight[find_pos].distance;
      }
    find_pos++;
  }
  return 0;
}

/* Determine if there is a route between from and to. */
void isflight(char *from, char *to)
{
  int d, dist;
  char anywhere[20];

  /* see if at destination */
  if(d=match(from, to)) {
    push(from, to, d);
    return;
  }
  /* try another connection */
  if(dist=find(from, anywhere)) {
    push(from, to, dist);
    isflight(anywhere, to);
  }
  else if(tos > 0) {
    /* backtrack */
    pop(from, to, &dist);
    isflight(from, to);
  }
}

/* Stack Routines */
void push(char *from, char *to, int dist)
{
  if(tos < MAX) {
    strcpy(bt_stack[tos].from,from);
    strcpy(bt_stack[tos].to,to);
    bt_stack[tos].dist = dist;
    tos++;
  }
  else printf("Stack full.\n");
}

void pop(char *from, char *to, int *dist)
{
  if(tos > 0) {
    tos--;
    strcpy(from,bt_stack[tos].from);
    strcpy(to,bt_stack[tos].to);
    *dist = bt_stack[tos].dist;
  }
  else printf("Stack underflow.\n");
}

listing 9
void isflight(char *from, char *to)
{
  int d, dist;
  char anywhere[20];

  while(dist=find(from, anywhere)) {
    /* breadth-first modification */
    if(d=match(anywhere, to)) {
      push(from, to, dist);
      push(anywhere, to, d);
      return;
    }
  }
  /* try any connection */
  if(dist=find(from, anywhere)) {
    push(from, to, dist);
    isflight(anywhere, to);
  }
  else if(tos>0) {
    pop(from, to, &dist);
    isflight(from, to);
  }
}

listing 10
/* Given from, find the farthest away "anywhere". */
int find(char *from, char *anywhere)
{
  int pos, dist;

  pos=dist = 0;
  find_pos = 0;

  while(find_pos < f_pos) {
    if(!strcmp(flight[find_pos].from, from) &&
      !flight[find_pos].skip) {
        if(flight[find_pos].distance>dist) {
        pos = find_pos;
        dist = flight[find_pos].distance;
      }
    }
    find_pos++;
  }
  if(pos) {
    strcpy(anywhere, flight[pos].to);
    flight[pos].skip = 1;
    return flight[pos].distance;
  }
  return 0;
}

listing 11
/* Hill-climbing */
#include <stdio.h>
#include <string.h>

 #define MAX 100

/* structure of the flight database */
struct FL {
  char from[20];
  char to[20];
  int distance;
  char skip; /* used for backtracking */
};

struct FL flight[MAX];  /* array of db structures */

int f_pos = 0;    /* number of entries in flight db */
int find_pos = 0; /* index for searching flight db */

int tos = 0;      /* top of stack */
struct stack {
  char from[20];
  char to[20];
  int dist;
} ;

struct stack bt_stack[MAX]; /* backtrack stack */

void setup(void), route(char *to);
void assert_flight(char *from, char *to, int dist);
void push(char *from, char *to, int dist);
void pop(char *from, char *to, int *dist);
void isflight(char *from, char *to);
int find(char *from, char *anywhere);
int match(char *from, char *to);

int main(void)
{
  char from[20], to[20];

  setup();

  printf("From? ");
  gets(from);
  printf("To? ");
  gets(to);

  isflight(from,to);
  route(to);

  return 0;
}

/* Initialize the flight database. */
void setup(void)
{
  assert_flight("New York", "Chicago", 1000);
  assert_flight("Chicago", "Denver", 1000);
  assert_flight("New York", "Toronto", 800);
  assert_flight("New York", "Denver", 1900);
  assert_flight("Toronto", "Calgary", 1500);
  assert_flight("Toronto", "Los Angeles", 1800);
  assert_flight("Toronto", "Chicago", 500);
  assert_flight("Denver", "Urbana", 1000);
  assert_flight("Denver", "Houston", 1500);
  assert_flight("Houston", "Los Angeles", 1500);
  assert_flight("Denver", "Los Angeles", 1000);
}

/* Put facts into the database. */
void assert_flight(char *from, char *to, int dist)
{

  if(f_pos < MAX) {
    strcpy(flight[f_pos].from, from);
    strcpy(flight[f_pos].to, to);
    flight[f_pos].distance = dist;
    flight[f_pos].skip = 0;
    f_pos++;
  }
  else printf("Flight database full.\n");
}

/* Show the route and the total distance. */
void route(char *to)
{
  int dist, t;

  dist = 0;
  t = 0;
  while(t < tos) {
    printf("%s to ", bt_stack[t].from);
    dist += bt_stack[t].dist;
    t++;
  }
  printf("%s\n", to);
  printf("Distance is %d.\n", dist);
}

/* If flight between from and to, then return
   the distance of flight; otherwise, return 0. */
int match(char *from, char *to)
{
  register int t;

  for(t=f_pos-1; t > -1; t--)
    if(!strcmp(flight[t].from, from) &&
      !strcmp(flight[t].to, to)) return flight[t].distance;

  return 0;  /* not found */
}

/* Given from, find the farthest away "anywhere". */
int find(char *from, char *anywhere)
{
  int pos, dist;

  pos=dist = 0;
  find_pos = 0;

  while(find_pos < f_pos) {
    if(!strcmp(flight[find_pos].from, from) &&
      !flight[find_pos].skip) {
        if(flight[find_pos].distance>dist) {
          pos = find_pos;
          dist = flight[find_pos].distance;
        }
    }
    find_pos++;
  }
  if(pos) {
    strcpy(anywhere, flight[pos].to);
    flight[pos].skip = 1;
    return flight[pos].distance;
  }
  return 0;
}

/* Determine if there is a route between from and to. */
void isflight(char *from, char *to)
{
  int d, dist;
  char anywhere[20];

  if(d=match(from, to)) {
    /* is goal */
    push(from, to, d);
    return;
  }

  /* find any connection */
  if(dist=find(from, anywhere)) {
    push(from, to, dist);
    isflight(anywhere, to);
  }
  else if(tos > 0) {
    pop(from, to, &dist);
    isflight(from, to);
  }
}

/* Stack Routines */
void push(char *from, char *to, int dist)
{
  if(tos < MAX) {
    strcpy(bt_stack[tos].from, from);
    strcpy(bt_stack[tos].to, to);
    bt_stack[tos].dist = dist;
    tos++;
  }
  else printf("Stack full.\n");
}

void pop(char *from, char *to, int *dist)
{
  if(tos > 0) {
    tos--;
    strcpy(from, bt_stack[tos].from);
    strcpy(to, bt_stack[tos].to);
    *dist = bt_stack[tos].dist;
  }
  else printf("Stack underflow.\n");
}

listing 12
/* Find closest "anywhere". */
int find(char *from, char *anywhere)
{
  int pos, dist;

  pos = 0;
  dist = 32000;  /* larger than the longest route */
  find_pos = 0;

  while(find_pos < f_pos) {
    if(!strcmp(flight[find_pos].from, from) &&
      !flight[find_pos].skip) {
        if(flight[find_pos].distance<dist) {
        pos = find_pos;
        dist = flight[find_pos].distance;
      }
    }
    find_pos++;
  }
  if(pos) {
    strcpy(anywhere, flight[pos].to);
    flight[pos].skip = 1;
    return flight[pos].distance;
  }
  return 0;
}

listing 13
int main(void)
{
  char from[20], to[20];

  setup();

  printf("From? ");
  gets(from);
  printf("To? ");
  gets(to);
  do {
    isflight(from, to);
    route(to);
    tos = 0;  /* reset the backtrack stack */
  } while(getchar() != 'q');

  return 0;
}

listing 14
/* Depth-first with multiple solutions
   using node removal */
#include <stdio.h>
#include <string.h>

#define MAX 100

/* structure of the flight database */
struct FL {
  char from[20];
  char to[20];
  int distance;
  char skip;   /* used in backtracking */
};

struct FL flight[MAX];

int f_pos = 0;    /* number of entries in flight db */
int find_pos = 0; /* index for searching flight db */

int tos = 0;      /* top of stack */
struct stack {
  char from[20];
  char to[20];
  int dist;
} ;
struct stack bt_stack[MAX]; /* backtrack stack */

void retract(char *from, char *to);
void clearmarkers(void);
void setup(void), route(char *to);
void assert_flight(char *from, char *to, int dist);
void push(char *from, char *to, int dist);
void pop(char *from, char *to, int *dist);
void isflight(char *from, char *to);
int find(char *from, char *anywhere);
int match(char *from, char *to);

int main(void)
{
  char from[20],to[20], c1[20], c2[20];
  int d;

  setup();

  printf("From? ");
  gets(from);
  printf("To? ");
  gets(to);
  do {
    isflight(from,to);
    route(to);
    clearmarkers(); /* reset the database */
    if(tos > 0) pop(c1,c2,&d);
    retract(c1,c2);  /* remove last node from database */
    tos = 0;  /* reset the backtrack stack */
  } while(getchar() != 'q');

  return 0;
}

/* Initialize the flight database. */
void setup(void)
{
  assert_flight("New York", "Chicago", 1000);
  assert_flight("Chicago", "Denver", 1000);
  assert_flight("New York", "Toronto", 800);
  assert_flight("New York", "Denver", 1900);
  assert_flight("Toronto", "Calgary", 1500);
  assert_flight("Toronto", "Los Angeles", 1800);
  assert_flight("Toronto", "Chicago", 500);
  assert_flight("Denver", "Urbana", 1000);
  assert_flight("Denver", "Houston", 1500);
  assert_flight("Houston", "Los Angeles", 1500);
  assert_flight("Denver", "Los Angeles", 1000);
}

/* Put facts into the database. */
void assert_flight(char *from, char *to, int dist)
{
  if(f_pos < MAX) {
    strcpy(flight[f_pos].from, from);
    strcpy(flight[f_pos].to, to);
    flight[f_pos].distance = dist;
    flight[f_pos].skip = 0;
    f_pos++;
  }
  else printf("Flight database full.\n");
}
/* Reset the "skip" field - i.e., re-activate all nodes. */
void clearmarkers()
{
  int t;

  for(t=0; t < f_pos; ++t) flight[t].skip = 0;
}

/* Remove an entry from the database. */
void retract(char *from, char *to)
{
  int t;

  for(t=0; t < f_pos; t++)
    if(!strcmp(flight[t].from, from) &&
      !strcmp(flight[t].to, to)) {
        strcpy(flight[t].from,"");
        return;

    }
}

/* Show the route and the total distance. */
void route(char *to)
{
  int dist, t;

  dist = 0;
  t = 0;
  while(t < tos) {
    printf("%s to ", bt_stack[t].from);
    dist += bt_stack[t].dist;
    t++;
  }
  printf("%s\n",to);
  printf("Distance is %d.\n", dist);
}

/* Given from, find anywhere. */
int find(char *from, char *anywhere)
{
  find_pos = 0;
  while(find_pos < f_pos) {
    if(!strcmp(flight[find_pos].from, from) &&
      !flight[find_pos].skip) {
        strcpy(anywhere, flight[find_pos].to);
        flight[find_pos].skip = 1;
        return flight[find_pos].distance;
      }
    find_pos++;
  }
  return 0;
}

/* If flight between from and to, then return
   the distance of flight; otherwise, return 0. */
int match(char *from, char *to)
{
  register int t;

  for(t=f_pos-1; t > -1; t--)
    if(!strcmp(flight[t].from, from) &&
      !strcmp(flight[t].to, to)) return flight[t].distance;

  return 0;  /* not found */
}

/* Determine if there is a route between from and to. */
void isflight(char *from, char *to)
{
  int d, dist;
  char anywhere[20];

  if(d=match(from, to)) {
    push(from, to, d); /* distance */
    return;
  }

  if(dist=find(from, anywhere)) {
    push(from, to, dist);
    isflight(anywhere, to);
  }
  else if(tos > 0) {
    pop(from, to, &dist);
    isflight(from, to);
  }
}

/* Stack Routines */
void push(char *from, char *to, int dist)
{
  if(tos < MAX) {
    strcpy(bt_stack[tos].from, from);
    strcpy(bt_stack[tos].to, to);
    bt_stack[tos].dist = dist;
    tos++;
  }
  else printf("Stack full.\n");
}

void pop(char *from, char *to, int *dist)
{
  if(tos > 0) {
  tos--;
    strcpy(from, bt_stack[tos].from);
    strcpy(to, bt_stack[tos].to);
    *dist = bt_stack[tos].dist;
  }
  else printf("Stack underflow.\n");
}

listing 15
/* Find the shortest distance. */
int route(void)
{
  int dist, t;
  static int old_dist = 32000;

  if(!tos) return 0;  /* all done */
  t = 0;
  dist = 0;
  while(t < tos) {
    dist += bt_stack[t].dist;
    t++;
  }

  /* if shorter, then make new solution */
  if(dist<old_dist && dist) {
    t = 0;
    old_dist = dist;
    stos = 0; /* clear old route from location stack */
    while(t < tos) {
      spush(bt_stack[t].from, bt_stack[t].to, bt_stack[t].dist);
      t++;
    }
  }
  return dist;
}

listing 16
/* Optimal solution using least-cost with
   route removal.
*/
#include <stdio.h>
#include <string.h>

#define MAX 100

/* structure of the flight database */
struct FL {
  char from[20];
  char to[20];
  int distance;
  char skip;  /* used for backtracking */
};

struct FL flight[MAX];  /* array of db structures */

int f_pos = 0;    /* number of entries in flight db */
int find_pos = 0; /* index for searching flight db */

int tos = 0;     /* top of stack */
int stos = 0;    /* top of solution stack */

struct stack {
  char from[20];
  char to[20];
  int dist;
} ;

struct stack bt_stack[MAX]; /* backtrack stack */
struct stack solution[MAX]; /* hold temporary solutions */

void setup(void);
int route(void);
void assert_flight(char *from, char *to, int dist);
void push(char *from, char *to, int dist);
void pop(char *from, char *to, int *dist);
void isflight(char *from, char *to);
void spush(char *from, char *to, int dist);
int find(char *from, char *anywhere);
int match(char *from, char *to);

int main(void)
{
  char from[20], to[20];
  int t, d;

  setup();

  printf("From? ");
  gets(from);
  printf("To? ");
  gets(to);
  do {
    isflight(from, to);
    d = route();
    tos = 0;  /* reset the backtrack stack */
  } while(d != 0);  /* while still finding solutions */

  t = 0;
  printf("Optimal solution is:\n");
  while(t < stos) {
    printf("%s to ", solution[t].from);
    d += solution[t].dist;
    t++;
  }
  printf("%s\n", to);
  printf("Distance is %d.\n", d);

  return 0;
}

/* Initialize the flight database. */
void setup(void)
{
  assert_flight("New York", "Chicago", 1000);
  assert_flight("Chicago", "Denver", 1000);
  assert_flight("New York", "Toronto", 800);
  assert_flight("New York", "Denver", 1900);
  assert_flight("Toronto", "Calgary", 1500);
  assert_flight("Toronto", "Los Angeles", 1800);
  assert_flight("Toronto", "Chicago", 500);
  assert_flight("Denver", "Urbana", 1000);
  assert_flight("Denver", "Houston", 1500);
  assert_flight("Houston", "Los Angeles", 1500);
  assert_flight("Denver", "Los Angeles", 1000);
}

/* Put facts into the database. */
void assert_flight(char *from, char *to, int dist)
{
  if(f_pos < MAX) {
    strcpy(flight[f_pos].from, from);
    strcpy(flight[f_pos].to, to);
    flight[f_pos].distance = dist;
    flight[f_pos].skip = 0;
    f_pos++;
  }
  else printf("Flight database full.\n");
}

/* Find the shortest distance. */
int route(void)
{
  int dist, t;
  static int old_dist=32000;

  if(!tos) return 0;  /* all done */
  t = 0;
  dist = 0;
  while(t < tos) {
    dist += bt_stack[t].dist;
    t++;
  }

  /* if shorter then make new solution */
  if(dist<old_dist && dist) {
    t = 0;
    old_dist = dist;
    stos = 0; /* clear old route from location stack */
    while(t < tos)  {
      spush(bt_stack[t].from, bt_stack[t].to, bt_stack[t].dist);
      t++;
    }
  }
  return dist;
}

/* If flight between from and to, then return
   the distance of flight; otherwise, return 0. */
int match(char *from, char *to)
{
  register int t;

  for(t=f_pos-1; t > -1; t--)
    if(!strcmp(flight[t].from, from) &&
      !strcmp(flight[t].to, to)) return flight[t].distance;

  return 0;  /* not found */
}

/* Given from, find anywhere. */
int find(char *from, char *anywhere)
{
  find_pos = 0;
  while(find_pos < f_pos) {
    if(!strcmp(flight[find_pos].from, from) &&
      !flight[find_pos].skip) {
        strcpy(anywhere, flight[find_pos].to);
        flight[find_pos].skip = 1;
        return flight[find_pos].distance;
    }
    find_pos++;
  }
  return 0;
}

/* Determine if there is a route between from and to. */
void isflight(char *from, char *to)
{
  int d, dist;
  char anywhere[20];

  if(d=match(from, to)) {
    push(from, to, d); /* distance */
    return;
  }

  if(dist=find(from, anywhere)) {

    push(from, to, dist);
    isflight(anywhere, to);
  }
  else if(tos > 0) {
    pop(from, to, &dist);
    isflight(from, to);
  }
}

/* Stack Routines */
void push(char *from, char *to, int dist)
{
  if(tos < MAX) {
    strcpy(bt_stack[tos].from, from);
    strcpy(bt_stack[tos].to, to);
    bt_stack[tos].dist = dist;
    tos++;
  }
  else printf("Stack full.\n");
}

void pop(char *from, char *to, int *dist)
{
  if(tos > 0) {
    tos--;
    strcpy(from, bt_stack[tos].from);
    strcpy(to, bt_stack[tos].to);
    *dist = bt_stack[tos].dist;
  }
  else printf("Stack underflow.\n");
}

/* Solution Stack */
void spush(char *from, char *to, int dist)
{
  if(stos < MAX) {
    strcpy(solution[stos].from, from);
    strcpy(solution[stos].to, to);
    solution[stos].dist = dist;
    stos++;
  }
  else printf("Shortest distance stack full.\n");
}

listing 17
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

