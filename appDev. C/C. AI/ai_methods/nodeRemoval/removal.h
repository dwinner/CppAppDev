#ifndef NODEREMOVAL_REMOVAL_H
#define NODEREMOVAL_REMOVAL_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

/* structure of the flight database */
struct FL
{
   char from[20];
   char to[20];
   int distance;
   char skip; /* used in backtracking */
};

struct stack {
   char from[20];
   char to[20];
   int dist;
};

extern int tos;

void retract(char *from, char *to);

void clearmarkers(void);

void setup(void), route(char *to);

void assert_flight(char *from, char *to, int dist);

void push(char *from, char *to, int dist);

void pop(char *from, char *to, int *dist);

void isflight(char *from, char *to);

int find(char *from, char *anywhere);

int match(char *from, char *to);

#endif//NODEREMOVAL_REMOVAL_H
