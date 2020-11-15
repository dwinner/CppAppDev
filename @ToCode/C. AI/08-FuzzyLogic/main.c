/*
 *  Main function for the Fuzzy Logic Battery Charge Control Simulator
 *
 *  ./software/ch9/main.c
 *
 *  mtj@cogitollc.com
 *
 */

#include <stdio.h>
#include "fuzzy.h"
#include "mtemp.h"

/*
 *  main()
 *
 *  Main program for the fuzzy logic sample application.
 *
 */

int main()
{
  int i;

  extern float timer;
  extern int simulate(void);
  extern void chargeControl( float * );

  extern float voltage;
  extern float temperature;
  extern int chargeMode;

  for (i = 0 ; i < 3000 ; i++) {

    simulate();

    chargeControl( &timer );

    timer += 1.0;

    printf("%d, %f, %f, %d\n", i, 
           voltage,
           temperature,
           chargeMode
    );

  }

  return 0;
}
