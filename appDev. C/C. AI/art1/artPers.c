#include "artPers.h"

/**
 * Small positive integer
 */
const float beta = 1.0;

/**
 * 0 <= vigilance < 1
 */
const float vigilance = 0.9;

int prototypeVector[TOTAL_PROTOTYPE_VECTORS][MAX_ITEMS];

/**
 * sumVector supports making recommendations.
 */
int sumVector[TOTAL_PROTOTYPE_VECTORS][MAX_ITEMS];

/**
 * Number of occupants of the cluster
 */
int members[TOTAL_PROTOTYPE_VECTORS];

/**
 * Identifies which cluster to which a particular customer belongs
 */
int membership[MAX_CUSTOMERS];

/**
 * String names for items in feature vector
 */
char *itemName[MAX_ITEMS] =
    {
        "Hammer",
        "Paper",
        "Snickers",
        "Screwdriver",
        "Pen",
        "Kit-Kat",
        "Wrench",
        "Pencil",
        "Heath-Bar",
        "Tape-Measure",
        "Binder"
    };

/**
 * Feature vectors are contained within the database array.
 * A one in the field represents a product that the customer has purchased.
 * A zero represents a product not purchased by the customer.
 */
int database[MAX_CUSTOMERS][MAX_ITEMS] =
    {
        /*     Hmr    Ppr    Snk    Scr    Pen    Kkt    Wrn    Pcl    Hth    Tpm     Bdr */
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},  //   3
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},  //  2
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0},  // 1
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},  //  2
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},  // 1
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},  //  2
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},  // 1
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},  //   3
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},  //  2
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0}   //   3
    };

/**
 * Number of populated prototype vectors
 */
int numPrototypeVectors = 0;

void displayCustomerDatabase(void)
{
   int customer, item, cluster;
   printf("\n");

   for (cluster = 0; cluster < TOTAL_PROTOTYPE_VECTORS; cluster++)
   {
      printf("ProtoVector %2d : ", cluster);
      for (item = 0; item < MAX_ITEMS; item++)
      {
         printf("%1d ", prototypeVector[cluster][item]);
      }

      printf("\n\n");
      for (customer = 0; customer < MAX_CUSTOMERS; customer++)
      {
         if (membership[customer] == cluster)
         {
            printf("Customer %2d    : ", customer);
            for (item = 0; item < MAX_ITEMS; item++)
            {
               printf("%1d ", database[customer][item]);
            }

            printf("  : %d : \n", membership[customer]);
         }
      }

      printf("\n");
   }

   printf("\n");
}

void initialize(void)
{
   int i, j;

   /* Clear out prototype vectors */
   for (i = 0; i < TOTAL_PROTOTYPE_VECTORS; i++)
   {
      for (j = 0; j < MAX_ITEMS; j++)
      {
         prototypeVector[i][j] = 0;
         sumVector[i][j] = 0;
      }

      members[i] = 0;
   }

   /* Initialize example vectors to no membership to any prototype vector */
   for (j = 0; j < MAX_CUSTOMERS; j++)
   {
      membership[j] = -1;
   }
}

int vectorMagnitude(int *vector)
{
   int j, total = 0;
   for (j = 0; j < MAX_ITEMS; j++)
   {
      if (vector[j] == 1)
      {
         total++;
      }
   }

   return total;
}

void vectorBitwiseAnd(int *result, int *v, int *w)
{
   int i;
   for (i = 0; i < MAX_ITEMS; i++)
   {
      result[i] = (v[i] && w[i]);
   }

}

int createNewPrototypeVector(int *example)
{
   int i, cluster;

   for (cluster = 0; cluster < TOTAL_PROTOTYPE_VECTORS; cluster++)
   {
      if (members[cluster] == 0)
      { break; }
   }

   if (cluster == TOTAL_PROTOTYPE_VECTORS) assert(0);

#ifdef DEBUG
   printf("Creating new cluster %d\n", cluster);
#endif

   numPrototypeVectors++;

   for (i = 0; i < MAX_ITEMS; i++)
   {
      prototypeVector[cluster][i] = example[i];
#ifdef DEBUG
      printf("%1d ", example[i]);
#endif
   }

   members[cluster] = 1;

#ifdef DEBUG
   printf("\n");
#endif

   return cluster;
}

void updatePrototypeVectors(int cluster)
{
   int item, customer, first = 1;

   assert(cluster >= 0);

#ifdef DEBUG
   printf("Recomputing prototypeVector %d (%d)\n", cluster, members[cluster]);
#endif

   for (item = 0; item < MAX_ITEMS; item++)
   {
      prototypeVector[cluster][item] = 0;
      sumVector[cluster][item] = 0;
   }

   for (customer = 0; customer < MAX_CUSTOMERS; customer++)
   {
      if (membership[customer] == cluster)
      {
         if (first)
         {
            for (item = 0; item < MAX_ITEMS; item++)
            {
               prototypeVector[cluster][item] = database[customer][item];
               sumVector[cluster][item] = database[customer][item];
            }

            first = 0;
         }
         else
         {
            for (item = 0; item < MAX_ITEMS; item++)
            {
               prototypeVector[cluster][item] =
                   prototypeVector[cluster][item] && database[customer][item];
               sumVector[cluster][item] += database[customer][item];
            }
         }
      }
   }
}

int performArt1(void)
{
   int andresult[MAX_ITEMS];
   int pvec, magPE, magP, magE;
   float result, test;
   int index, done = 0;
   int count = 50;

   while (!done)
   {
      done = 1;

      for (index = 0; index < MAX_CUSTOMERS; index++)
      {

#ifdef DEBUG
         printf("\nExample %d (currently in %d)\n", index, membership[index]);
#endif

         /* Step 3 */
         for (pvec = 0; pvec < TOTAL_PROTOTYPE_VECTORS; pvec++)
         {

            if (members[pvec])
            {

#ifdef DEBUG
               printf("Test vector %d (members %d)\n", pvec, members[pvec]);
#endif

               vectorBitwiseAnd(andresult,
                                &database[index][0], &prototypeVector[pvec][0]);

               magPE = vectorMagnitude(andresult);
               magP = vectorMagnitude(&prototypeVector[pvec][0]);
               magE = vectorMagnitude(&database[index][0]);

               result = (float) magPE / (beta + (float) magP);

               test = (float) magE / (beta + (float) MAX_ITEMS);

#ifdef DEBUG
               printf("step 3 : %f > %f ?\n", result, test);
#endif

               if (result > test)
               {

                  /* Test for vigilance acceptability */

#ifdef DEBUG
                  printf("step 4 : testing vigilance %f < %f\n",
                   ((float)magPE/(float)magE), vigilance);
#endif

                  if (((float) magPE / (float) magE) < vigilance)
                  {

                     int old;

                     /* Ensure this is a different cluster */
                     if (membership[index] != pvec)
                     {

                        old = membership[index];
                        membership[index] = pvec;

#ifdef DEBUG
                        printf("Moved example %d from cluster %d to %d\n",
                        index, old, pvec);
#endif

                        if (old >= 0)
                        {
                           members[old]--;
                           if (members[old] == 0)
                           { numPrototypeVectors--; }
                        }
                        members[pvec]++;

                        /* Recalculate the prototype vectors for the old and new
                         * clusters.
                         */
                        if ((old >= 0) && (old < TOTAL_PROTOTYPE_VECTORS))
                        {
                           updatePrototypeVectors(old);
                        }

                        updatePrototypeVectors(pvec);

                        done = 0;
                        break;

                     }
                     else
                     {
                        /* Already in this cluster */
                     }

                  } /* vigilance test */

               }

            }

         } /* for vector loop */

         /* Check to see if the current vector was processed */
         if (membership[index] == -1)
         {
            /* No prototype vector was found to be close to the example
             * vector.  Create a new prototype vector for this example.
             */
            membership[index] = createNewPrototypeVector(&database[index][0]);
            done = 0;
         }

      } /* customers loop */

#ifdef DEBUG
      printf("\n");
#endif

      if (!count--)
      { break; }

   } /* !done */

   return 0;
}

void makeRecommendation(int customer)
{
   int bestItem = -1;
   int val = 0;
   int item;

   for (item = 0; item < MAX_ITEMS; item++)
   {
      if ((database[customer][item] == 0) &&
          (sumVector[membership[customer]][item] > val))
      {
         bestItem = item;
         val = sumVector[membership[customer]][item];
      }

   }

   printf("For Customer %d, ", customer);

   if (bestItem >= 0)
   {
      printf("The best recommendation is %d (%s)\n",
             bestItem, itemName[bestItem]);
      printf("Owned by %d out of %d members of this cluster\n",
             sumVector[membership[customer]][bestItem],
             members[membership[customer]]);
   }
   else
   {
      printf("No recommendation can be made.\n");
   }

   printf("Already owns: ");
   for (item = 0; item < MAX_ITEMS; item++)
   {
      if (database[customer][item])
      { printf("%s ", itemName[item]); }
   }
   printf("\n\n");
}
