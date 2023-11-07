#ifndef EMSAPOP_H
#define EMSAPOP_H

#include "common.h"

/**
 * @brief Count of checks on diagonal 
 */
#define DIAG_CHECK_COUNT  4

/**
 * @brief Population
 */
//Member_type Population[MAX_MEMBERS];

/**
 * @brief Initialize the population of candidate solutions
 */
void InitializePopulation(void);

/**
 * @brief Randomly perturb an encoded solution
 * @param member Member
 */
void TweakSolution(Member_type* member);

/**
 * @brief Emit a solution in chessboard form
 * @param member Member
 */
void EmitSolution(const Member_type* member);

/**
 * @brief Calculates the energy of the passed solution.
 * @details The energy is the number of conflicts on the board.
 * Keep in mind that only diagonals are checked. The encoding ensures that
 * no vertical or horizontal conflicts are possible
 * @param member Member
 * @return Computed energy
 */
float ComputeEnergy(const Member_type* member);

/**
 * @brief Perform the simulated annealing algorithm
 * @param curTemp Current temperature
 * @return Solution status
 */
int SimulateAnnealing(float curTemp);

/**
 * @brief Run through the population and compute the energy for each
 */
void ComputeAllEnergy(void);

#endif // EMSAPOP_H
