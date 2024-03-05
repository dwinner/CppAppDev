#ifndef LONGESTDISTANCE_HILLCLIMBING_H
#define LONGESTDISTANCE_HILLCLIMBING_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

/**
 * structure of the flight database
 */
struct Flight
{
   char from[20];
   char to[20];
   int distance;
   bool skip; /* used for backtracking */
};

struct Stack
{
   char from[20];
   char to[20];
   int dist;
};

/**
 * Initialize the flight database
 */
void setup(void);

/**
 * Show the route and the total distance
 * @param to Target
 */
void route(char *to);

/**
 * Put facts into the database.
 * @param from From item
 * @param to To item
 * @param distance Distance
 */
void assertFlight(char *from, char *to, int distance);

/* Stack Routines */
void push(char *from, char *to, int distance);
void pop(char *from, char *to, int *poDistance);

/**
 * Determine if there is a route between from and to.
 * @param from Source
 * @param to Target
 */
void isFlight(char *from, char *to);

/**
 * Given from, find the farthest away "anywhere".
 * @param from Source
 * @param anywhere The farthest target
 * @return Distance
 */
int find(char *from, char *anywhere);

/**
 * If flight between from and to, then return the distance of flight; otherwise, return 0.
 * @param from Source
 * @param to Target
 * @return Distance of flight, or 0.
 */
int match(char *from, char *to);

#endif//LONGESTDISTANCE_HILLCLIMBING_H
