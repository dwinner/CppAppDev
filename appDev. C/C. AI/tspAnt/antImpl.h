#ifndef TSPANT_ANTIMPL_H
#define TSPANT_ANTIMPL_H

#include "common.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>

extern double distance[MAX_CITIES][MAX_CITIES];
extern double pheromone[MAX_CITIES][MAX_CITIES];
extern double best;
extern int bestIndex;

/**
 * @brief Initialize the cities, their distances and the Ant population.
 */
void init(void);

/**
 * @brief Reinitialize the ant population to start another tour around the graph.
 */
void restartAnts(void);

/**
 * @brief Compute the denominator for the path probability equation
 * @details Concentration of pheromone of the current path over the sum of
 * all concentrations of available paths
 * @param from Source
 * @param to Destination
 * @return Denominator
 */
double antProduct(int from, int to);

/**
 * @brief Using the path probability selection algorithm and the current pheromone
 * levels of the graph, select the next city the antIndex will travel to.
 * @param antIndex The antIndex number
 * @return The next city to travel
 */
int selectNextCity(int antIndex);

/**
 * @brief Simulate a single step for each ant in the population.
 * This function will return zero once all ants have completed their tours.
 * @return 0 if all ants have finished their travelling.
 */
int simulateAnts(void);

/**
 * @brief Update the pheromone levels on each ant based upon the number of ants
 * that have travelled over it, including evaporation of existing pheromone.
 */
void updateTrails(void);

/**
 * @brief For the ant with the best tour (shortest tour through the graph),
 * emit the path in two data files (plotted together).
 * @param ant The ant number
 */
void emitDataFile(int ant);

#endif//TSPANT_ANTIMPL_H
