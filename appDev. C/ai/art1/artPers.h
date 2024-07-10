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
void displayCustomerDb(void);

/**
 * Initialize the prototype vectors, clusters and all other necessary structures.
 */
void init(void);

/**
 * Compute the magnitude of the poVector passed in.
 * The magnitude is the number of '1' bits that are set in the poVector.
 * @param poVector Vector
 * @return The magnitude
 */
int vectorMagnitude(const int *poVector);

/**
 * Perform a bitwise and of two vectors (resulting in another vector).
 * @param result
 * @param poVector1 1St vector
 * @param poVector2 2Nd vector
 */
void vectorBitwiseAnd(int *result, const int *poVector1, const int *poVector2);

/**
 * Create a new prototype vector (new cluster) given the passed poExample vector.
 * @param poExample Example vector
 * @return Cluster value
 */
int createNewPrototypeVector(const int *poExample);

/**
 * Recompute the prototype vector for the given cluster passed in.
 * @param cluster Cluster
 */
void updatePrototypeVectors(int cluster);

/**
 * Perform the ART1 (Adaptive Resonance Theory) algorithm.
 * @return Status code
 */
int performArt1(void);

/**
 * Given a customer feature vector and the prototype vector, choose the
 * item within the vector that the customer feature vector does not have
 * (is 0) and has the highest sumVector for the cluster.
 * @param customer Customer Id
 */
void makeRecommendation(int customer);

#endif //ART1_ARTPERS_H
