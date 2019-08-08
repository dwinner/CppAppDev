//
// Created by Vinevtsev on 8/8/2019.
//

#ifndef VIAHASHING_HASH_CELL_H
#define VIAHASHING_HASH_CELL_H

#ifndef MAX
#define MAX 260
#endif

struct hashType
{
   int index;  /* logical index */
   int val;    /* actual value of the array element */
   struct hashType *next;  /* pointer to next value with the same hash */
} primary[MAX];

/**
 * Initialize the hash array
 */
void init(void);

/**
 * Compute hash and store value
 *
 * @param cell_name Cell name
 * @param value Value to store
 */
void store(char *cell_name, int value);

/**
 * Add elements to the collision list
 *
 * @param i
 * @param start
 */
void slstore(struct hashType *i, struct hashType *start);

/**
 * Compute hash and return value
 *
 * @param cell_name
 * @return
 */
int find(char *cell_name);

#endif //VIAHASHING_HASH_CELL_H
