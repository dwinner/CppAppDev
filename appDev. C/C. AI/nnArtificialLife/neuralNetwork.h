//
// Artificial Life Simulation Functions
//

#ifndef NNARTIFICIALLIFE_NEURALNETWORK_H
#define NNARTIFICIALLIFE_NEURALNETWORK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "common.h"

extern int landscape[DIM][MAX_GRID][MAX_GRID];
extern agentType agents[MAX_AGENTS];
extern int agentCount;
extern int agentTypeCounts[2];
extern int agentMaxAge[2];
extern int agentBirths[2];
extern int agentDeaths[2];
extern agentType *agentMaxPtr[2];
extern int agentTypeReproductions[2];
extern agentType bestAgent[2];
extern int agentMaxGen[2];
extern plantType plants[MAX_PLANTS];
extern int plantCount;

/* Command line parameters */
extern int seedPopulation;
extern int emitRuntimeTrend;
extern int noGrow;
extern int carn2Plant;
extern int noRepro;
extern int step;

#define AGENTS	"agents.dat"
#define STATS	"stats.dat"
#define RUNTIME "runtime.dat"

/**
 * @brief Finds an empty spot
 * @details Given a pointer to an agent, find an empty spot for the agent within
 *  its particular type plane.
 * @param agent Agent
 */
void findEmptySpot( agentType *agent );

/**
 * @brief Init agent
 * @details Initialize the agent passed by reference.
 * @param agent Agent
 */
void initAgent( agentType *agent );

/**
 * @brief Grow a single plant using the index into the plants array.
 * @param i Plant index
 */
void growPlant( int i );

/**
 * @brief This is the overall initialization routine for the simulation. It
 *  initialize the plants and agents. If the population is not being
 *  seeded, the agents are all created randomly. Otherwise, the agents
 *  are not random but instead read from the file.
 */
void init( void );

/**
 * @brief This function emits the landscape to the terminal. To slow the display
 *  down, a busy loop is provided at the end. The termination value may be
 *  changed depending upon the speed of your system.
 */
void emitLandscape( void );

/**
 * @brief Clip the coordinate to provide the toroid.
 * @param z approximated int
 * @return clipped value
 */
int clip( int z );

/**
 * @brief Calculate the values of the input vector for the neural network.
 * @param x Abscissa
 * @param y Ordinate
 * @param inputs Input for planes
 * @param offsets Offset array
 * @param neg Inverse mark of the motion
 */
void percept( int x, int y, short *inputs,const offsetPairType *offsets, int neg );

/**
 * @brief Implement the turn action. Given a turn action, the current facing
 *  is used to determine the new facing.
 * @param action Turn action
 * @param agent Agent
 */
void turn ( int action, agentType *agent );

/**
 * @brief Implements the move function. The offsets vector is used to
 *  determine the new coordinates for an agent based upon its
 *  current coordinates and facing (direction).
 * @param agent Agent
 */
void move( agentType *agent );

/**
 * @brief Kill the agent passed by reference to the function.  The agent may have
 *  died because of starvation, or because it was eaten by a predator.
 *  Before the agent is removed, it is checked to see if it was the longest
 *  living agent (of the particular type), and if so is saved.  If space is
 *  available for a new agent (< 50% maximum for the agent type), then a
 *  new agent is created.
 * @param agent Agent
 */
void killAgent( agentType *agent );

/**
 * @brief An agent has reached the energy level needed for reproduction. An agent
 *  is only permitted to reproduce if space is available for the new agent.
 *  The child agent is a copy of the parent, except that one of the weights
 *  of the neural network is mutated.
 * @param agent Agent
 */
void reproduceAgent( agentType *agent );

/**
 * @brief Given a plane and a set of coordinates, find an object on that plane
 *  within the proximity of the agent (based upon offsets and neg). If
 *  an object is found, a value of 1 is returned with the object's
 *  coordinates in ox/oy. Otherwise, 0 is returned.
 * @param plane Plane
 * @param ax Start X
 * @param ay Start Y
 * @param offsets Offset arrau
 * @param neg Neg value as a motion direction
 * @param ox Offset X
 * @param oy Offset Y
 * @return 1 if object is found, 0 otherwise
 */
int chooseObject( int plane, int ax, int ay,const offsetPairType *offsets,int neg, int *ox, int *oy );

/**
 * @brief This function implements the eat action for agents. The agent has
 *  a given direction, and based upon this direction, the chooseObject
 *  function is called to identify an object that can be eaten. If an
 *  object is found to be eaten, the energy level is checked to see if
 *  asexual reproduction is permitted.  When a plant is eaten by an
 *  herbivore, the growPlant function is called to grow a new plant.
 *  Similarly, if an herbivore is eaten by a carnivore, the herbivore
 *  is killed and possible replaced based upon the current number of
 *  herbivores in the environment.
 * @param agent Agent
 */
void eat( agentType *agent );

/**
 * @brief This is the main agent simulation routine.  This function performs
 *  the perception phase which fills in the input cells for the agent's
 *  neural network.  This is based upon the particular direction of the
 *  agent.  The neural network is then forward propogated to determine
 *  the action to be taken.  A function is then called based upon the
 *  action selected.  The agent's energy is decremented (since all
 *  agent's use energy while they are alive).  If the agent's energy
 *  falls to or below zero, the agent is killed.
 * @param agent Agent
 */
void simulateAgent( agentType *agent );

/**
 * @brief The simulate function permits each agent to be simulated for one
 *  iteration. Herbivores are permitted to perform one iteration first
 *  and then the carnivores.
 */
void simulate( void );

/**
 * @brief Emit help information for the application.
 * @param prog The program
 */
void emitHelp( char *prog );

/**
 * @brief This function emits statistics data to the trend file.  Information
 *  archived includes agent maximum ages, number of agents of each type,
 *  and the number of reproductions per agent type.  Similar information
 *  is also emitted to standard output.
 * @param fp File
 * @param i Agent's index
 */
void emitTrend2File( FILE *fp, int i );

/**
 * @brief This function emits the two best agents to the agents.dat file.
 *  The most successful agents are stored with the bestAgent structure.
 */
void emitAgents2File( void );

/**
 * @brief This function emits runtime trend information to the runtime.dat
 *  file. This data is specific to playback of successful agents
 *  after evolution is complete.
 * @param rfp File
 * @param i Agent's index
 */
void emitRuntimeTrend2File( FILE *rfp, int i );

#endif //NNARTIFICIALLIFE_NEURALNETWORK_H
