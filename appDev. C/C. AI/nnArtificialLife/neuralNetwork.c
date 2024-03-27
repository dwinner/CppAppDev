#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "neuralNetwork.h"

int landScape[DIM][MAX_GRID][MAX_GRID];
AgentT agents[MAX_AGENTS];
int agentCount = 0;
int agentTypeCounts[2] = {0, 0};
int agentMaxAge[2] = {0, 0};
int agentBirths[2] = {0, 0};
int agentDeaths[2] = {0, 0};
AgentT *agentMaxPtr[2];
int agentTypeReproductions[2] = {0, 0};
AgentT bestAgent[2];
int agentMaxGen[2] = {0, 0};
PlantT plants[MAX_PLANTS];
int plantCount = 0;

/* Command line parameters */
int seedPopulation;
int emitRuntimeTrend = 0;
int noGrow = 0;
int carn2Plant = 0;
int noRepro = 0;
int step = 0;

void findEmptySpot(AgentT *agent)
{
   agent->location.x = -1;
   agent->location.y = -1;

   while (1)
   {
      agent->location.x = getRand(MAX_GRID);
      agent->location.y = getRand(MAX_GRID);
      if (landScape[agent->type][agent->location.y][agent->location.x] == 0)
      {
         break;
      }
   }

   agent->direction = getRand(MAX_DIRECTION);
   landScape[agent->type][agent->location.y][agent->location.x]++;
}

void initAgent(AgentT *agent)
{
   int i;

   agent->energy = (MAX_ENERGY / 2);
   agent->age = 0;
   agent->generation = 1;
   agentTypeCounts[agent->type]++;
   findEmptySpot(agent);

   if (seedPopulation == 0)
   {
      for (i = 0; i < (MAX_INPUTS * MAX_OUTPUTS); i++)
      {
         agent->weight_oi[i] = getWeight();
      }

      for (i = 0; i < MAX_OUTPUTS; i++)
      {
         agent->biaso[i] = getWeight();
      }
   }
}

void growPlant(int plantIndex)
{
   int x, y;

   while (1)
   {
      x = getRand(MAX_GRID);
      y = getRand(MAX_GRID);

      if (landScape[PLANT_PLANE][y][x] == 0)
      {

         plants[plantIndex].location.x = (short) x;
         plants[plantIndex].location.y = (short) y;
         landScape[PLANT_PLANE][y][x]++;
         break;
      }
   }
}

void init(void)
{
   /* Initialize the landScape */
   memset(landScape, 0, sizeof(int) * DIM * MAX_GRID * MAX_GRID);
   memset(bestAgent, 0, sizeof(AgentT) * 2);

   /* Initialize the plant plane */
   for (plantCount = 0; plantCount < MAX_PLANTS; plantCount++)
   {
      growPlant(plantCount);
   }

   if (seedPopulation == 0)
   {
      /* Randomly initialize the Agents */
      for (agentCount = 0; agentCount < MAX_AGENTS; agentCount++)
      {
         if (agentCount < (MAX_AGENTS / 2))
         {
            agents[agentCount].type = TYPE_HERBIVORE;
         }
         else
         {
            agents[agentCount].type = TYPE_CARNIVORE;
         }

         initAgent(&agents[agentCount]);
      }
   }
   else
   {
      /* In this case, we're seeding the population with the agents stored
         within the agents.dat file. */
      FILE *fp;
      int offset;

      /* Try to seed the population from a file */
      fp = fopen(AGENTS, "r");

      fread(&bestAgent[0], sizeof(AgentT), 1, fp);
      fread(&bestAgent[1], sizeof(AgentT), 1, fp);

      for (agentCount = 0; agentCount < MAX_AGENTS; agentCount++)
      {
         offset = agentCount < MAX_AGENTS / 2 ? 0 : 1;
         memcpy((void *) &agents[agentCount], (void *) &bestAgent[offset],
                sizeof(AgentT));
         findEmptySpot(&agents[agentCount]);
         agents[agentCount].energy = MAX_ENERGY;
         agentTypeCounts[agents[agentCount].type]++;
      }
   }
}

void emitLandscape(void)
{
   int x, y;
   volatile int i;

   system("clear");

   for (y = 0; y < MAX_GRID; y++)
   {
      printf("\n%2d : ", y);

      for (x = 0; x < MAX_GRID; x++)
      {
         if (landScape[CARN_PLANE][y][x] != 0)
         {
            printf("C ");
         }
         else if (landScape[HERB_PLANE][y][x] != 0)
         {
            printf("H ");
         }
         else if (landScape[PLANT_PLANE][y][x] != 0)
         {
            printf("P ");
         }
         else
         {
            printf("  ");
         }
      }
   }

   /* Slow down, so that we can watch the behavior */
   for (i = 0; i < 10000000; i++)
   {}
}

int clip(int valToClip)
{
   if (valToClip > MAX_GRID - 1)
   {
      valToClip = (valToClip % MAX_GRID);
   }
   else if (valToClip < 0)
   {
      valToClip = (MAX_GRID + valToClip);
   }

   return valToClip;
}

void percept(int x, int y, short *inputs, const OffsetPairT *offsets, int neg)
{
   int plane, i;
   int xOffset, yOffset;

   for (plane = HERB_PLANE; plane <= PLANT_PLANE; plane++)
   {
      inputs[plane] = 0;
      i = 0;

      while (offsets[i].xOffset != 9)
      {
         xOffset = x + (offsets[i].xOffset * neg);
         yOffset = y + (offsets[i].yOffset * neg);
         xOffset = clip(xOffset);
         yOffset = clip(yOffset);
         if (landScape[plane][yOffset][xOffset] != 0)
         {
            inputs[plane]++;
         }

         i++;
      }
   }
}

void turn(int action, AgentT *agent)
{
   switch (agent->direction)
   {
      case NORTH:
         if (action == ACTION_TURN_LEFT)
         {
            agent->direction = WEST;
         }
         else
         {
            agent->direction = EAST;
         }
         break;

      case SOUTH:
         if (action == ACTION_TURN_LEFT)
         {
            agent->direction = EAST;
         }
         else
         {
            agent->direction = WEST;
         }
         break;

      case EAST:
         if (action == ACTION_TURN_LEFT)
         {
            agent->direction = NORTH;
         }
         else
         {
            agent->direction = SOUTH;
         }
         break;

      case WEST:
         if (action == ACTION_TURN_LEFT)
         {
            agent->direction = SOUTH;
         }
         else
         {
            agent->direction = NORTH;
         }
         break;
   }
}

void move(AgentT *agent)
{
   const OffsetPairT offsets[4] =
       {
           {-1, 0},
           {1,  0},
           {0,  1},
           {0,  -1}
       };

   landScape[agent->type][agent->location.y][agent->location.x]--;
   agent->location.x = (short) clip(agent->location.x + offsets[agent->direction].xOffset);
   agent->location.y = (short) clip(agent->location.y + offsets[agent->direction].yOffset);
   landScape[agent->type][agent->location.y][agent->location.x]++;
}

void killAgent(AgentT *agent)
{
   agentDeaths[agent->type]++;

   /* Death came to this agent (or it was eaten)...  */
   landScape[agent->type][agent->location.y][agent->location.x]--;
   agentTypeCounts[agent->type]--;

   if (agent->age > bestAgent[agent->type].age)
   {
      memcpy((void *) &bestAgent[agent->type], (void *) agent, sizeof(AgentT));
   }

   if (carn2Plant && (agent->type == TYPE_CARNIVORE))
   {
      if (landScape[PLANT_PLANE][agent->location.y][agent->location.x] == 0)
      {
         int i;
         for (i = 0; i < MAX_PLANTS; i++)
         {
            if (plants[i].location.x == -1)
            {
               break;
            }
         }

         if (i < MAX_PLANTS)
         {
            plants[i].location.x = agent->location.x;
            plants[i].location.y = agent->location.y;
            landScape[PLANT_PLANE][agent->location.y][agent->location.x]++;
         }

         agent->location.x = -1;
         agent->location.y = -1;
      }
   }

   /* 50% of the agent spots are reserved for asexual reproduction.
    * If we fall under this, we create a new random agent.
    */
   if (agentTypeCounts[agent->type] < (MAX_AGENTS / 4))
   {
      if (seedPopulation == 0)
      {
         /* Create a new agent */
         initAgent(agent);
      }
      else
      {
         agent->location.x = -1;
         agent->location.y = -1;
         agent->type = TYPE_DEAD;
      }
   }
   else
   {
      agent->location.x = -1;
      agent->location.y = -1;
      agent->type = TYPE_DEAD;
   }
}

void reproduceAgent(AgentT *agent)
{
   AgentT *child;
   int i;

   /* Don't allow an agent type to occupy more than half of the available
      agent slots. */
   if (agentTypeCounts[agent->type] < (MAX_AGENTS / 2))
   {
      /* Find an empty spot and copy the agent, mutating one of the
         weights or biases. */
      for (i = 0; i < MAX_AGENTS; i++)
      {
         if (agents[i].type == TYPE_DEAD)
         {
            break;
         }
      }

      if (i < MAX_AGENTS)
      {
         child = &agents[i];
         memcpy((void *) child, (void *) agent, sizeof(AgentT));
         findEmptySpot(child);
         if (getSRand() <= 0.2)
         {
            child->weight_oi[getRand(TOTAL_WEIGHTS)] = getWeight();
         }

         child->generation = (short) (child->generation + 1);
         child->age = 0;
         if (agentMaxGen[child->type] < child->generation)
         {
            agentMaxGen[child->type] = child->generation;
         }

         /* Reproducing halves the parent's energy */
         child->energy = agent->energy = (MAX_ENERGY / 2);
         agentTypeCounts[child->type]++;
         agentTypeReproductions[child->type]++;
      }
   }
}

int chooseObject(int plane, int ax, int ay, const OffsetPairT *offsets, int neg, int *ox, int *oy)
{
   int xOffset, yOffset, i = 0;

   while (offsets[i].xOffset != 9)
   {
      xOffset = ax + (offsets[i].xOffset * neg);
      yOffset = ay + (offsets[i].yOffset * neg);
      xOffset = clip(xOffset);
      yOffset = clip(yOffset);
      if (landScape[plane][yOffset][xOffset] != 0)
      {
         *ox = xOffset;
         *oy = yOffset;
         return 1;
      }

      i++;
   }

   return 0;
}

void eat(AgentT *agent)
{
   int plane = 0, ax, ay, ox, oy, ret = 0;

   if (agent->type == TYPE_CARNIVORE)
   {
      plane = HERB_PLANE;
   }
   else if (agent->type == TYPE_HERBIVORE)
   {
      plane = PLANT_PLANE;
   }

   ax = agent->location.x;
   ay = agent->location.y;

   switch (agent->direction)
   {
      case NORTH:
         ret = chooseObject(plane, ax, ay, northProx, 1, &ox, &oy);
         break;

      case SOUTH:
         ret = chooseObject(plane, ax, ay, northProx, -1, &ox, &oy);
         break;

      case WEST:
         ret = chooseObject(plane, ax, ay, westProx, 1, &ox, &oy);
         break;

      case EAST:
         ret = chooseObject(plane, ax, ay, westProx, -1, &ox, &oy);
         break;

   }

   /* Found an object -- eat it! */
   if (ret)
   {
      int i;
      if (plane == PLANT_PLANE)
      {
         for (i = 0; i < MAX_PLANTS; i++)
         {
            if ((plants[i].location.x == ox) && (plants[i].location.y == oy))
            {
               break;
            }
         }

         if (i < MAX_PLANTS)
         {
            agent->energy += MAX_FOOD_ENERGY;
            if (agent->energy > MAX_ENERGY)
            {
               agent->energy = MAX_ENERGY;
            }

            landScape[PLANT_PLANE][oy][ox]--;
            if (noGrow == 0)
            {
               growPlant(i);
            }
            else
            {
               plants[i].location.x = -1;
               plants[i].location.y = -1;
            }
         }
      }
      else
      {
         for (i = 0; i < MAX_AGENTS; i++)
         {
            if ((agents[i].location.x == ox) && (agents[i].location.y == oy))
            {
               break;
            }
         }

         if (i < MAX_AGENTS)
         {
            agent->energy += (MAX_FOOD_ENERGY * 2);
            if (agent->energy > MAX_ENERGY)
            {
               agent->energy = MAX_ENERGY;
            }

            killAgent(&agents[i]);
         }
      }

      if (agent->energy > (REPRODUCE_ENERGY * MAX_ENERGY))
      {
         if (noRepro == 0)
         {
            reproduceAgent(agent);
            agentBirths[agent->type]++;
         }
      }
   }
}

void simulateAgent(AgentT *agent)
{
   int x, y;
   int out, in;
   int largest, winner;

   x = agent->location.x;
   y = agent->location.y;

   /* Determine inputs for the agent neural network */
   switch (agent->direction)
   {
      case NORTH:
         percept(x, y, &agent->inputs[HERB_FRONT], northFront, 1);
         percept(x, y, &agent->inputs[HERB_LEFT], northLeft, 1);
         percept(x, y, &agent->inputs[HERB_RIGHT], northRight, 1);
         percept(x, y, &agent->inputs[HERB_PROXIMITY], northProx, 1);
         break;

      case SOUTH:
         percept(x, y, &agent->inputs[HERB_FRONT], northFront, -1);
         percept(x, y, &agent->inputs[HERB_LEFT], northLeft, -1);
         percept(x, y, &agent->inputs[HERB_RIGHT], northRight, -1);
         percept(x, y, &agent->inputs[HERB_PROXIMITY], northProx, -1);
         break;

      case WEST:
         percept(x, y, &agent->inputs[HERB_FRONT], westFront, 1);
         percept(x, y, &agent->inputs[HERB_LEFT], westLeft, 1);
         percept(x, y, &agent->inputs[HERB_RIGHT], westRight, 1);
         percept(x, y, &agent->inputs[HERB_PROXIMITY], westProx, 1);
         break;

      case EAST:
         percept(x, y, &agent->inputs[HERB_FRONT], westFront, -1);
         percept(x, y, &agent->inputs[HERB_LEFT], westLeft, -1);
         percept(x, y, &agent->inputs[HERB_RIGHT], westRight, -1);
         percept(x, y, &agent->inputs[HERB_PROXIMITY], westProx, -1);
         break;
   }

   /* Forward propagate the inputs through the neural network */
   for (out = 0; out < MAX_OUTPUTS; out++)
   {
      /* Initialize the output node with the bias */
      agent->actions[out] = agent->biaso[out];

      /* Multiply the inputs by the weights for this output node */
      for (in = 0; in < MAX_INPUTS; in++)
      {
         int inc = agent->inputs[in] * agent->weight_oi[(out * MAX_INPUTS) + in];
         agent->actions[out] += inc;
      }
   }

   largest = -9;
   winner = -1;

   /* Select the largest node (winner-takes-all network) */
   for (out = 0; out < MAX_OUTPUTS; out++)
   {
      if (agent->actions[out] >= largest)
      {
         largest = agent->actions[out];
         winner = out;
      }
   }

   /* Perform Action */
   switch (winner)
   {
      case ACTION_TURN_LEFT:
      case ACTION_TURN_RIGHT:
         turn(winner, agent);
         break;

      case ACTION_MOVE:
         move(agent);
         break;

      case ACTION_EAT:
         eat(agent);
         break;

      default:
         break;
   }

   /* Consume some amount of energy */
   if (agent->type == TYPE_HERBIVORE)
   {
      agent->energy -= 2;
   }
   else
   {
      agent->energy -= 1;
   }

   /* If energy falls to or below zero, the agent dies.  Otherwise, we
    * check to see if the agent has lived longer than any other agent
    * of the particular type.
    */
   if (agent->energy <= 0)
   {
      killAgent(agent);
   }
   else
   {
      agent->age++;
      if (agent->age > agentMaxAge[agent->type])
      {
         agentMaxAge[agent->type] = agent->age;
         agentMaxPtr[agent->type] = agent;
      }
   }
}

void simulate(void)
{
   int i, type;

   /* Simulate the herbivores first, then the carnivores */
   for (type = TYPE_HERBIVORE; type <= TYPE_CARNIVORE; type++)
   {
      for (i = 0; i < MAX_AGENTS; i++)
      {
         if (agents[i].type == type)
         {
            simulateAgent(&agents[i]);
         }
      }
   }
}

void emitHelp(char *program)
{
   printf("\n\t%s [-ph]\n\n", program);
   printf("\t\t-h\tHelp\n");
   printf("\t\t-p\tPlayback mode\n");
   printf("\t\t-r\tSave Runtime Trend Data to File\n");
   printf("\t\t-g\tDon't regrow plants\n");
   printf("\t\t-c\tConvert Carnivores to Plants\n");
   printf("\t\t-n\tNo reproduction is permitted\n");
   printf("\t\t-s\tManual Step\n");
   printf("\n");
   exit(0);
}

void emitTrend2File(FILE *outFile, int agentIdx)
{
   printf("Time: %7d : Max Age [%d %d] Count [%d %d]"
          " Repro [%d %d] Gen [%d %d]\n",
          agentIdx, agentMaxAge[0], agentMaxAge[1],
          agentTypeCounts[0], agentTypeCounts[1],
          agentTypeReproductions[0], agentTypeReproductions[1],
          agentMaxGen[0], agentMaxGen[1]);

   fprintf(outFile, "%d %d %d %d %d %d %d\n",
           agentIdx, agentMaxAge[0], agentMaxAge[1],
           agentTypeCounts[0], agentTypeCounts[1],
           agentTypeReproductions[0], agentTypeReproductions[1]);
}

void emitAgents2File(void)
{
   FILE *fp;
   int i;

   for (i = 0; i < 1; i++)
   {
      if (agentMaxPtr[i]->age > bestAgent[i].age)
      {
         memcpy((void *) &bestAgent[i],
                (void *) agentMaxPtr[i], sizeof(AgentT));
      }
   }

   /* Write the two best agents to a file */
   fp = fopen(AGENTS, "wb");
   for (i = 0; i < 2; i++)
   {
      fwrite(&bestAgent[i], sizeof(AgentT), 1, fp);
   }

   fclose(fp);
}

void emitRuntimeTrend2File(FILE *outFile, int agentIdx)
{
   int j;

   fprintf(outFile, "%d %d %d %d %d\n", agentIdx,
           agentBirths[0], agentBirths[1],
           agentDeaths[0], agentDeaths[1]);
   fflush(outFile);

   for (j = 0; j < 2; j++)
   {
      agentBirths[j] = 0;
      agentDeaths[j] = 0;
   }
}

#pragma clang diagnostic pop