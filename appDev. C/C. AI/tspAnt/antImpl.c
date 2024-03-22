#include "antImpl.h"

cityType cities[MAX_CITIES];
antType ants[MAX_ANTS];

/**
 * @brief From and To distances
 */
double distance[MAX_CITIES][MAX_CITIES];

/**
 * @brief From and To pheromones
 */
double pheromone[MAX_CITIES][MAX_CITIES];

double best = (double) MAX_TOUR;
int bestIndex;

void init(void)
{
   int from, to, antIdx;

   /* Create the cities and their locations */
   for (from = 0; from < MAX_CITIES; from++)
   {
      /* Randomly place cities around the grid */
      cities[from].x = getRand(MAX_DISTANCE);
      cities[from].y = getRand(MAX_DISTANCE);
      for (to = 0; to < MAX_CITIES; to++)
      {
         distance[from][to] = 0.0;
         pheromone[from][to] = INIT_PHEROMONE;
      }
   }

   /* Compute the distances for each of the cities on the map */
   for (from = 0; from < MAX_CITIES; from++)
   {
      for (to = 0; to < MAX_CITIES; to++)
      {
         if ((to != from) && (distance[from][to] == 0.0))
         {
            int deltaX = abs(cities[from].x - cities[to].x);
            int deltaY = abs(cities[from].y - cities[to].y);
            distance[from][to] = sqrt((deltaX * deltaX) + (deltaY * deltaY));
            distance[to][from] = distance[from][to];
         }
      }
   }

   /* Initialize the ants */
   to = 0;
   for (antIdx = 0; antIdx < MAX_ANTS; antIdx++)
   {
      /* Distribute the ants to each of the cities uniformly */
      if (to == MAX_CITIES)
      {
         to = 0;
      }

      ants[antIdx].curCity = to++;
      for (from = 0; from < MAX_CITIES; from++)
      {
         ants[antIdx].tabu[from] = 0;
         ants[antIdx].path[from] = -1;
      }

      ants[antIdx].pathIndex = 1;
      ants[antIdx].path[0] = ants[antIdx].curCity;
      ants[antIdx].nextCity = -1;
      ants[antIdx].tourLength = 0.0;

      /* Load the antIdx's current city into taboo */
      ants[antIdx].tabu[ants[antIdx].curCity] = 1;
   }
}

void restartAnts(void)
{
   int antIdx, i, to = 0;

   for (antIdx = 0; antIdx < MAX_ANTS; antIdx++)
   {
      if (ants[antIdx].tourLength < best)
      {
         best = ants[antIdx].tourLength;
         bestIndex = antIdx;
      }

      ants[antIdx].nextCity = -1;
      ants[antIdx].tourLength = 0.0;

      for (i = 0; i < MAX_CITIES; i++)
      {
         ants[antIdx].tabu[i] = 0;
         ants[antIdx].path[i] = -1;
      }

      if (to == MAX_CITIES)
      {
         to = 0;
      }

      ants[antIdx].curCity = to++;
      ants[antIdx].pathIndex = 1;
      ants[antIdx].path[0] = ants[antIdx].curCity;
      ants[antIdx].tabu[ants[antIdx].curCity] = 1;
   }
}

double antProduct(int from, int to)
{
   return ((pow(pheromone[from][to], ALPHA) *
            pow((1.0 / distance[from][to]), BETA)));
}

int selectNextCity(int antIndex)
{
   int from, to;
   double denominator = 0.0;

   /* Choose the next city to visit */
   from = ants[antIndex].curCity;

   /* Compute denominator */
   for (to = 0; to < MAX_CITIES; to++)
   {
      if (ants[antIndex].tabu[to] == 0)
      {
         denominator += antProduct(from, to);
      }
   }

   assert(denominator != 0.0);

   do
   {
      double product;
      to++;
      if (to >= MAX_CITIES)
      {
         to = 0;
      }

      if (ants[antIndex].tabu[to] == 0)
      {
         product = antProduct(from, to) / denominator;
         if (getSRand() < product)
         {
            break;
         }
      }

   } while (1);

   return to;
}

int simulateAnts(void)
{
   int antIdx;
   int moving = 0;

   for (antIdx = 0; antIdx < MAX_ANTS; antIdx++)
   {
      /* Ensure this ant still has cities to visit */
      if (ants[antIdx].pathIndex < MAX_CITIES)
      {
         ants[antIdx].nextCity = selectNextCity(antIdx);
         ants[antIdx].tabu[ants[antIdx].nextCity] = 1;
         ants[antIdx].path[ants[antIdx].pathIndex++] = ants[antIdx].nextCity;
         ants[antIdx].tourLength += distance[ants[antIdx].curCity][ants[antIdx].nextCity];

         /* Handle the final case (last city to first) */
         if (ants[antIdx].pathIndex == MAX_CITIES)
         {
            ants[antIdx].tourLength +=
                distance[ants[antIdx].path[MAX_CITIES - 1]][ants[antIdx].path[0]];
         }

         ants[antIdx].curCity = ants[antIdx].nextCity;
         moving++;
      }
   }

   return moving;
}

void updateTrails(void)
{
   int from, to, i, antIdx;

   /* Pheromone Evaporation */
   for (from = 0; from < MAX_CITIES; from++)
   {
      for (to = 0; to < MAX_CITIES; to++)
      {
         if (from != to)
         {
            pheromone[from][to] *= (1.0 - RHO);
            if (pheromone[from][to] < 0.0)
            {
               pheromone[from][to] = INIT_PHEROMONE;
            }
         }
      }
   }

   /* Add new pheromone to the trails */

   /* Look at the tours of each antIdx */
   for (antIdx = 0; antIdx < MAX_ANTS; antIdx++)
   {
      /* Update each leg of the tour given the tour length */
      for (i = 0; i < MAX_CITIES; i++)
      {
         if (i < MAX_CITIES - 1)
         {
            from = ants[antIdx].path[i];
            to = ants[antIdx].path[i + 1];
         }
         else
         {
            from = ants[antIdx].path[i];
            to = ants[antIdx].path[0];
         }

         pheromone[from][to] += (Q_VALUE / ants[antIdx].tourLength);
         pheromone[to][from] = pheromone[from][to];
      }
   }

   for (from = 0; from < MAX_CITIES; from++)
   {
      for (to = 0; to < MAX_CITIES; to++)
      {
         pheromone[from][to] *= RHO;
      }
   }
}

void emitDataFile(int ant)
{
   int city;
   FILE *fp;

   fp = fopen("cities.dat", "w");
   for (city = 0; city < MAX_CITIES; city++)
   {
      fprintf(fp, "%d %d\n", cities[city].x, cities[city].y);
   }

   fclose(fp);

   fp = fopen("solution.dat", "w");
   for (city = 0; city < MAX_CITIES; city++)
   {
      fprintf(fp, "%d %d\n",
              cities[ants[ant].path[city]].x,
              cities[ants[ant].path[city]].y);
   }
   fprintf(fp, "%d %d\n",
           cities[ants[ant].path[0]].x,
           cities[ants[ant].path[0]].y);

   fclose(fp);
}
