//
// Artificial Life Simulation Types and Symbolic Constants
//

#ifndef NNARTIFICIALLIFE_COMMON_H
#define NNARTIFICIALLIFE_COMMON_H

#include <math.h>
#include <stdlib.h>

/* Sensor Input Cells */

#define HERB_FRONT   0
#define CARN_FRONT   1
#define PLANT_FRONT   2
#define HERB_LEFT   3
#define CARN_LEFT   4
#define PLANT_LEFT   5
#define HERB_RIGHT   6
#define CARN_RIGHT   7
#define PLANT_RIGHT   8
#define HERB_PROXIMITY   9
#define CARN_PROXIMITY   10
#define PLANT_PROXIMITY   11

#define MAX_INPUTS   12


/* Output Cells */

#define ACTION_TURN_LEFT   0
#define ACTION_TURN_RIGHT   1
#define ACTION_MOVE      2
#define ACTION_EAT      3

#define MAX_OUTPUTS   4


/* Total number of weights (and biases) for an agent */

#define TOTAL_WEIGHTS   ((MAX_INPUTS * MAX_OUTPUTS) + MAX_OUTPUTS)


/* Description of the 3 planes for the 2d grid */

#define HERB_PLANE   0
#define CARN_PLANE   1
#define PLANT_PLANE   2


/* Available directions */

#define NORTH   0
#define SOUTH   1
#define EAST   2
#define WEST   3

#define MAX_DIRECTION   4


/* Types for location, plants and agents */

typedef struct
{
   short x;
   short y;
} LocationT;

typedef struct
{
   LocationT location;
} PlantT;

typedef struct
{
   short type;
   short energy;
   short parent;
   short age;
   short generation;
   LocationT location;
   unsigned short direction;
   short inputs[MAX_INPUTS];
   short weight_oi[MAX_INPUTS * MAX_OUTPUTS];
   short biaso[MAX_OUTPUTS];
   short actions[MAX_OUTPUTS];
} AgentT;

#define TYPE_HERBIVORE   (0)
#define TYPE_CARNIVORE   (1)
#define TYPE_DEAD   (-1)

typedef struct
{
   short yOffset;
   short xOffset;
} OffsetPairT;


/* Grid offsets for Front/Left/Right/Proximity (North/-South facing) */
extern const OffsetPairT northFront[];
extern const OffsetPairT northLeft[];
extern const OffsetPairT northRight[];
extern const OffsetPairT northProx[];

/* Grid offsets for Front/Left/Right/Proximity (West/-East facing) */
extern const OffsetPairT westFront[];
extern const OffsetPairT westLeft[];
extern const OffsetPairT westRight[];
extern const OffsetPairT westProx[];

/* Macro Function Definitions */

#define getSRand()   ((float)rand() / (float)RAND_MAX)
#define getRand(x)   (int)((x) * getSRand())

#define getWeight()   (getRand(9)-1)


/* Parameters that can be adjusted */

#define MAX_FOOD_ENERGY      15
#define MAX_ENERGY      60
#define REPRODUCE_ENERGY   0.9

#define MAX_AGENTS   36

#define MAX_PLANTS   35

#define DIM 3
#define MAX_GRID   30

#define MAX_STEPS   1000000

#endif //NNARTIFICIALLIFE_COMMON_H
