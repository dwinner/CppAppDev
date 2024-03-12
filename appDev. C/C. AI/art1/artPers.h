#ifndef ART1_ARTPERS_H
#define ART1_ARTPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define MAX_ITEMS      (11)
#define MAX_CUSTOMERS      (10)
#define TOTAL_PROTOTYPE_VECTORS   (5)

/**
 * Emit each Prototype Vector with all occupant customer feature vectors.
 */
void displayCustomerDatabase( void );

/**
 * Initialize the prototype vectors, clusters and all other necessary structures.
 */
void initialize( void );

/**
 * Compute the magnitude of the vector passed in.
 * The magnitude is the number of '1' bits that are set in the vector.
 * @param vector Vector
 * @return The magnitude
 */
int vectorMagnitude( int *vector );

/**
 * Perform a bitwise and of two vectors (resulting in another vector).
 * @param result
 * @param v 1St vector
 * @param w 2Nd vector
 */
void vectorBitwiseAnd( int *result, int *v, int *w );

/**
 * Create a new prototype vector (new cluster) given the passed example vector.
 * @param example Example vector
 * @return Cluster value
 */
int createNewPrototypeVector( int *example );

/**
 * Recompute the prototype vector for the given cluster passed in.
 * @param cluster Cluster
 */
void updatePrototypeVectors( int cluster );

/**
 * Perform the ART1 (Adaptive Resonance Theory) algorithm.
 * @return Status code
 */
int performArt1( void );

/**
 * Given a customer feature vector and the prototype vector, choose the
 * item within the vector that the customer feature vector does not have
 * (is 0) and has the highest sumVector for the cluster.
 * @param customer Customer Id
 */
void makeRecommendation ( int customer );

#endif //ART1_ARTPERS_H
