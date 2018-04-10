#ifndef EMSAPOP_H
#define EMSAPOP_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "common.h"

/**
 * \brief Population
 */
Member_type Population[MAX_MEMBERS];

/**
 * \brief Initialize the population of candidate solutions
 */
void initializePopulation(void);

/**
 * \brief Randomly perturb an encoded solution
 * \param member Member
 */
void tweakSolution(Member_type* member);

/**
 * \brief Emit a solution in chessboard form
 * \param member Member
 */
void emitSolution(Member_type* member);

/**
 * \brief Calculates the energy of the passed solution.
 * \details The energy is the number of conflicts on the board.
 * Note that only diagonals are checked. The encoding ensures that
 * no vertical or horizontal conflicts are possible
 * \param member Member
 * \return Computed energy
 */
float computeEnergy(Member_type* member);

/**
 * \brief Perform the simulated annealing algorithm
 * \param curTemp Current temperature
 * \return Solution status
 */
int simulateAnnealing(float curTemp);

/**
 * \brief Run through the population and compute the energy for each
 */
void computeAllEnergy(void);

#endif // EMSAPOP_H
