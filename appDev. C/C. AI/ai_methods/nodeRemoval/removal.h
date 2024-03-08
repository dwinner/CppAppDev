#ifndef NODEREMOVAL_REMOVAL_H
#define NODEREMOVAL_REMOVAL_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

/**
 * structure of the flightDb database
 */
typedef struct
{
   char from[20];
   char to[20];
   int distance;
   bool skip; /* used in backtracking */
} FlightItemT;

typedef struct
{
   char from[20];
   char to[20];
   int distance;
} StackT;

extern int stackTop;

/**
 * Remove an entry from the database.
 * @param from Source
 * @param to Target
 */
void retract(char *from, char *to);

/**
 * Reset the "skip" field - i.e., re-activate all nodes.
 */
void clearMarkers(void);

/**
 * Initialize the flightDb database.
 */
void setup(void);

/**
 * Show the route and the total distance.
 * @param to Destination
 */
void route(char *to);

/**
 * Put facts into the database.
 * @param from Source
 * @param to Destination
 * @param distance Distance
 */
void assertFlight(char *from, char *to, int distance);

/**
 * Determine if there is a route between from and to.
 * @param from Source
 * @param to Target
 */
void isFlight(char *from, char *to);

/**
 * Given from, find anywhere.
 * @param from Source
 * @param anywhere Destination
 * @return Distance
 */
int find(char *from, char *anywhere);

/**
 * If flightDb between from and to, then return the distance of fligh tDb;
 * otherwise, return 0.
 * @param from Source
 * @param to Target
 * @return Distance
 */
int match(char *from, char *to);

/* Stack Routines */
void push(char *from, char *to, int distance);
void pop(char *from, char *to, int *poDistance);

#endif//NODEREMOVAL_REMOVAL_H
