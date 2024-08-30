#ifndef DEPTHSEARCH_DEPTH1ST_H
#define DEPTHSEARCH_DEPTH1ST_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITEMS 100
#define STR_CAPACITY 20

/**
 * Flight stack
 */
typedef struct Stack
{
   /**
    * Route from
    */
   char from[STR_CAPACITY];

   /**
    * Route to
    */
   char to[STR_CAPACITY];

   /**
    * Distance
    */
   int distance;
} FlightStackT;

/**
 * Flight database type
 */
typedef struct Flight
{
   /**
    * From city
    */
   char from[STR_CAPACITY];

   /**
    * To city
    */
   char to[STR_CAPACITY];

   /**
    * Distance
    */
   int distance;

   /**
    * Used in backtracking
    */
   bool skipped;
} FlightDbT;

/**
 * Array of db structures
 */
extern FlightDbT flightStorage[MAX_ITEMS];

/**
 * The number of entries in flight db
 */
extern int flightPosition;

/**
 * Index for searching flight db
 */
extern int findPosition;

/**
 * The top of stack
 */
extern int topPosition;

/**
 * Initialize the flight database
 */
void setup(void);

/**
 * Show the route and total distance
 * @param to Route to
 */
void route(char *to);

/**
 * Put facts into the database
 * @param from  From route
 * @param to    To route
 * @param aDistance  distance
 */
void assertFlight(char *from, char *to, int aDistance);

/**
 * Determine if there is a route between from and to
 * @param from  Route from
 * @param to    Route to
 */
void isFlight(char *from, char *to);

/**
 * Given from, find anywhere
 * @param from      Route from
 * @param anywhere  Route to anywhere
 * @return          The distance between routes
 */
int find(char *from, char *anywhere);

/**
 * If flight between from and to exists, then return the distance of flight,
 * otherwise, return 0.
 * @param from  Route from
 * @param to    Route to
 * @return      The distance of flight
 */
int match(char *from, char *to);

/**
 * Push to the flight stack
 * @param from  Route from
 * @param to    Route to
 * @param aDistance  Distance
 */
void push(char *from, char *to, int aDistance);

/**
 * Pop from the flight stack
 * @param from  Route from
 * @param to    Route to
 * @param poDistance  Distance
 */
void pop(char *from, char *to, int *poDistance);

#endif //DEPTHSEARCH_DEPTH1ST_H
