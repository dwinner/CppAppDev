#ifndef SHORTESTDISTANCE_SD_H
#define SHORTESTDISTANCE_SD_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

/* structure of the flight database */
struct FL
{
   char from[20];
   char to[20];
   int distance;
   char skip;  /* used for backtracking */
};

struct stack
{
   char from[20];
   char to[20];
   int dist;
};

extern int tos;
extern int stos;
extern struct stack solution[];

void setup(void);

int route(void);

void assert_flight(char *from, char *to, int dist);

void push(char *from, char *to, int dist);

void pop(char *from, char *to, int *dist);

void isflight(char *from, char *to);

void spush(char *from, char *to, int dist);

int find(char *from, char *anywhere);

int match(char *from, char *to);

#endif //SHORTESTDISTANCE_SD_H
