/*
 *  Rules based system timer routines
 *
 *  ./software/ch8/timers.c
 *
 *  mtj@cogitollc.com
 *
 */

#include <stdio.h>
#include "common.h"

timerType timers[MAX_TIMERS];


/*
 *  fireTimer()
 *
 *  Fire the defined timer.  This involves adding a '(timer-triggered x)'
 *  fact to the working memory, with x='expired timer'.
 *
 */

int fireTimer( int timerIndex )
{
  int ret;
  char element[MEMORY_ELEMENT_SIZE+1];

  extern int performAddCommand( char *mem );

  sprintf( element, "(timer-triggered %d)", timerIndex );

  ret = performAddCommand( element );

  timers[timerIndex].active = 0;

  return ret;
}


/*
 *  startTimer()
 *
 *  Activate a timer with a given expiration time.
 *
 */

void startTimer( int index, int expiration )
{
  timers[index].expiration = expiration;
  timers[index].active = 1;

  return;
}


/*
 *  processTimers()
 *
 *  Process the active timer list, upon finding an expired timer, 
 *  fire it.
 *
 */

void processTimers( void )
{
  int i;

  for (i = 0 ; i < MAX_TIMERS ; i++) {

    if (timers[i].active) {

      if (--timers[i].expiration == 0) {

        fireTimer( i );

      }

    }

  }

  return;
}
