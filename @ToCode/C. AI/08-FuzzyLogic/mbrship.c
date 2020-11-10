/*
 *  Fuzzy Logic Membership Functions
 *
 *  ./software/ch9/membership.c
 *
 *  mtj@cogitollc.com
 *
 */

#include "fuzzy.h"


/*
 *  normalize()
 *
 *  Normalize the fuzzy logic value.
 *
 */

int normalize( fuzzyType in )
{
  if (in >= 0.5) return 1;
  else return 0;
}


/*
 *  spikeProfile()
 *
 *  Return the fuzzified value given the spike profile.
 *
 */

fuzzyType spikeProfile( float value, float lo, float high )
{
  float peak;

  value += (-lo);

  if      ((lo < 0) && (high < 0)) {
    high = -(high - lo);
  } else if ((lo < 0) && (high > 0)) {
    high += -lo;
  } else if ((lo > 0) && (high > 0)) {
    high -= lo;
  }

  peak = (high / 2.0);
  lo = 0.0;

  if        (value < peak) {
    return( value / peak );
  } else if (value > peak) {
    return( (high-value) / peak );
  } 

  return 1.0;
}


/*
 *  plateauProfile()
 *
 *  Return the fuzzified value given the plateau profile.
 *
 */

fuzzyType plateauProfile( float value, float lo, float lo_plat,
                          float hi_plat, float hi )
{
  float upslope;
  float downslope;

  value += (-lo);

  if (lo < 0.0) {
    lo_plat += -lo;  hi_plat += -lo;
    hi      += -lo;  lo       = 0;
  } else {
    lo_plat -= lo;  hi_plat -= lo;
    hi      -= lo;  lo       = 0;
  }

  upslope = (1.0 / (lo_plat - lo));
  downslope = (1.0 / (hi - hi_plat));

  if      (value < lo) return 0.0;
  else if (value > hi) return 0.0;
  else if ((value >= lo_plat) && (value <= hi_plat)) return 1.0;
  else if (value < lo_plat) return ((value-lo) * upslope);
  else if (value > hi_plat) return ((hi-value) * downslope);

  return 0.0;
}


/*
 *  m_temp_hot()
 *
 *  Return the fuzzified value using the hot (temperature)
 *  membership function.  The hot membership function uses
 *  the plateau profile.
 *
 */

fuzzyType m_temp_hot( float temp )
{
  const float lo = 35.0;
  const float lo_plat = 45.0;
  const float hi_plat = 45.0;
  const float hi = 45.0;

  if (temp < lo) return 0.0;
  if (temp > hi) return 1.0;

  return plateauProfile( temp, lo, lo_plat, hi_plat, hi );
}


/*
 *  m_temp_warm()
 *
 *  Return the fuzzified value using the warm (temperature)
 *  membership function.  The warm membership function uses
 *  the plateau profile.
 *
 */

fuzzyType m_temp_warm( float temp )
{
  const float lo = 15.0;
  const float lo_plat = 25.0;
  const float hi_plat = 35.0;
  const float hi = 45.0;

  if ((temp < lo) || (temp > hi)) return 0.0;

  return plateauProfile( temp, lo, lo_plat, hi_plat, hi );
}


/*
 *  m_temp_cold()
 *
 *  Return the fuzzified value using the cold (temperature)
 *  membership function.  The cold membership function uses
 *  the plateau profile.
 *
 */

fuzzyType m_temp_cold( float temp )
{
  const float lo = 15.0;
  const float lo_plat = 15.0;
  const float hi_plat = 15.0;
  const float hi = 25.0;

  if (temp < lo) return 1.0;
  if (temp > hi) return 0.0;

  return plateauProfile( temp, lo, lo_plat, hi_plat, hi );
}


/*
 *  m_voltage_low()
 *
 *  Return the fuzzified value using the low (voltage)
 *  membership function.  The low membership function uses
 *  the plateau profile.
 *
 */

fuzzyType m_voltage_low( float voltage )
{
  const float lo = 5.0;
  const float lo_plat = 5.0;
  const float hi_plat = 5.0;
  const float hi = 10.0;

  if (voltage < lo) return 1.0;
  if (voltage > hi) return 0.0;

  return plateauProfile( voltage, lo, lo_plat, hi_plat, hi );
}


/*
 *  m_voltage_medium()
 *
 *  Return the fuzzified value using the medium (voltage)
 *  membership function.  The medium membership function 
 *  uses the plateau profile.
 *
 */

fuzzyType m_voltage_medium( float voltage )
{
  const float lo = 5.0;
  const float lo_plat = 10.0;
  const float hi_plat = 20.0;
  const float hi = 25.0;

  if (voltage < lo) return 0.0;
  if (voltage > hi) return 0.0;

  return plateauProfile( voltage, lo, lo_plat, hi_plat, hi );
}


/*
 *  m_voltage_high()
 *
 *  Return the fuzzified value using the high (voltage)
 *  membership function.  The high membership function 
 *  uses the plateau profile.
 *
 */

fuzzyType m_voltage_high( float voltage )
{
  const float lo = 25.0;
  const float lo_plat = 30.0;
  const float hi_plat = 30.0;
  const float hi = 30.0;

  if (voltage < lo) return 0.0;
  if (voltage > hi) return 1.0;

  return plateauProfile( voltage, lo, lo_plat, hi_plat, hi );
}
