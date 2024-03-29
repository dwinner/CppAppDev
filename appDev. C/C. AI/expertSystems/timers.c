#include "timers.h"

int fireTimer(int timerIndex)
{
   int returnValue;
   
   char element[MEMORY_ELEMENT_SIZE+1];

   extern int performAddCommand( char *mem );

   sprintf( element, "(timer-triggered %d)", timerIndex );

   returnValue = performAddCommand(element );

   timers[timerIndex].active = 0;

   return returnValue;
}

void startTimer(int index, int expiration)
{
   timers[index].expiration = expiration;
   timers[index].active = 1;
}

void processTimers(void)
{
   int i;

   for (i = 0 ; i < MAX_TIMERS ; i++) {

      if (timers[i].active) {

         if (--timers[i].expiration == 0) {

            fireTimer( i );

         }

      }

   }
}
