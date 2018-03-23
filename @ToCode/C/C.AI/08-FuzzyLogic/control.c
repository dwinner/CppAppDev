/*
 *  Fuzzy Logic Simulated Battery Charge Controller
 *
 *  ./software/ch9/control.c
 *
 *  mtj@cogitollc.com
 *
 */

#include <stdio.h>
#include "fuzzy.h"
#include "mtemp.h"

int chargeMode = TRICKLE_CHARGE;


/*
 *  chargeControl()
 *
 *  Given temperature and voltage values, use the fuzzy logic 
 *  membership functions and fuzzy operators to determine the
 *  charge mode.
 *
 */

void chargeControl( float *timer )
{
  static unsigned int i = 0;

  extern float voltage, temperature;

  if ( (i++ % 10) == 0 ) {

    if (normalize( m_voltage_high( voltage ) ) ) {
      chargeMode = TRICKLE_CHARGE;
      *timer = 0.0;
    } else if (normalize( m_temp_hot( temperature ) ) ) {
      chargeMode = TRICKLE_CHARGE;
      *timer = 0.0;
    } else if (normalize( 
                   fuzzyAnd( fuzzyNot( m_voltage_high( voltage ) ),
                             fuzzyNot( m_temp_hot( temperature ) ) ) ) ) {
      chargeMode = FAST_CHARGE;
      *timer = 0.0;
    }

  }

  printf( "%d, %f, %f %d\n", i, voltage, temperature, chargeMode );
}
