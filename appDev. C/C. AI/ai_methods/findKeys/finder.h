#ifndef FINDKEYS_FINDER_H
#define FINDKEYS_FINDER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

/**
 * Structure of the keys database
 */
typedef struct
{
   char from[20];
   char to[20];
   bool skipped;
} KeyTypeT;

typedef struct
{
   char from[20];
   char to[20];
} StackT;

/**
 * Initialize the database.
 */
void setup(void);

/**
 * Show the route to the keys.
 */
void route(void);

/**
 * Put facts into the database.
 * @param from Source
 * @param to Target
 */
void assertKeys(char *from, char *to);

void push(char *from, char *to);

void pop(char *from, char *to);

/**
 * Determine if there is a route between from and to.
 * @param from Source
 * @param to Target
 */
void isKeys(char *from, char *to);

/**
 * Given from, find anywhere.
 * @param from Source
 * @param anywhere Destination
 * @return true if found, false otherwise
 */
bool find(char *from, char *anywhere);

/**
 * See if there is a match.
 * @param from Source
 * @param to Target
 * @return true if found, false - otherwise
 */
bool match(char *from, char *to);

#endif //FINDKEYS_FINDER_H
