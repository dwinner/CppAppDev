#include <stdio.h>
#include "neuralNetwork.h"

int main (int argc, char *argv[])
{
   int i, c;
   FILE *fp = NULL, *rfp = NULL;

   seedPopulation = 0;

   /*
    *  Parse all options from the command line.
    */
   while (1) {

      if ((c = getopt( argc, argv, "prgcnsh")) > 0) {

         switch( c ) {

            case 'p':
               /* Playback mode */
               seedPopulation = 1;
               break;

            case 'r':
               /* Save Runtime trend data (useful in playback) */
               emitRuntimeTrend = 1;
               break;

            case 'g':
               /* Don't Grow plants */
               noGrow = 1;
               break;

            case 'c':
               /* Carnivores become Plants after death */
               carn2Plant = 1;
               break;

            case 'n':
               /* No reproduction */
               noRepro = 1;
               break;

            case 's':
               /* Manual step */
               step = 1;
               break;

            case 'h':
               emitHelp( argv[0] );
               break;

         }

      } else break;

   }

   /* Seed the random number generator */
   srand( time(NULL) );

   /* If we're in playback mode, don't do stats */
   if (seedPopulation == 0) {
      fp = fopen(STATS, "w");
   }

   if (emitRuntimeTrend == 1) {
      rfp = fopen(RUNTIME, "w");
   }

   /* Initialize the simulation */
   init();

   /* Main loop for the simulation.  */
   for (i = 0 ; i < MAX_STEPS ; i++) {

      /* Emit the landscape to the terminal if we're in playback mode. */
      if (seedPopulation) emitLandscape();

      /* Await user return before continuing */
      if (step) {
         (void)getchar();
      }

      /* Simulate each agent for one time step */
      simulate();

      /* Emit data at some low rate */
      if (seedPopulation == 0) {
         if ((i % 100) == 0) {
            emitTrend2File( fp, i );
         }
      } else {
         if ((agentTypeCounts[0] == 0) && (agentTypeCounts[1] == 0)) break;
      }

      /* For playback trend data, emit each time step */
      if (emitRuntimeTrend) {
         emitRuntimeTrend2File( rfp, i );
      }

   }

   if (seedPopulation == 0) {
      fclose(fp);
      emitAgents2File();
   }

   if (emitRuntimeTrend) {
      fclose(rfp);
   }

   return 0;
}
