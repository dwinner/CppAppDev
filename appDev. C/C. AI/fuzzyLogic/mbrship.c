//
// Created by Man on 4/3/2024.
//

#include "mbrship.h"

int normalize(fuzzyType in)
{
   if (in >= 0.5)
      return 1;
   else
      return 0;
}

fuzzyType spikeProfile(float value, float lo, float high)
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

fuzzyType plateauProfile(float value, float lo, float loPlat, float hiPlat, float hi)
{
   float upslope;
   float downslope;

   value += (-lo);

   if (lo < 0.0) {
      loPlat += -lo;  hiPlat += -lo;
      hi      += -lo;  lo       = 0;
   } else {
      loPlat -= lo;  hiPlat -= lo;
      hi      -= lo;  lo       = 0;
   }

   upslope = (1.0 / (loPlat - lo));
   downslope = (1.0 / (hi - hiPlat));

   if      (value < lo) return 0.0F;
   else if (value > hi) return 0.0F;
   else if ((value >= loPlat) && (value <= hiPlat)) return 1.0F;
   else if (value < loPlat) return ((value-lo) * upslope);
   else if (value > hiPlat) return ((hi-value) * downslope);

   return 0.0F;
}

fuzzyType mTempHot(float temperature)
{
   const float lo = 35.0;
   const float lo_plat = 45.0;
   const float hi_plat = 45.0;
   const float hi = 45.0;

   if (temperature < lo) return 0.0;
   if (temperature > hi) return 1.0;

   return plateauProfile( temperature, lo, lo_plat, hi_plat, hi );
}

fuzzyType mTempWarm(float temperature)
{
   const float lo = 15.0;
   const float lo_plat = 25.0;
   const float hi_plat = 35.0;
   const float hi = 45.0;

   if ((temperature < lo) || (temperature > hi)) return 0.0;

   return plateauProfile( temperature, lo, lo_plat, hi_plat, hi );
}

fuzzyType mTempCold(float temperature)
{
   const float lo = 15.0;
   const float lo_plat = 15.0;
   const float hi_plat = 15.0;
   const float hi = 25.0;

   if (temperature < lo) return 1.0;
   if (temperature > hi) return 0.0;

   return plateauProfile( temperature, lo, lo_plat, hi_plat, hi );
}

fuzzyType mVoltageLow(float voltage)
{
   const float lo = 5.0;
   const float lo_plat = 5.0;
   const float hi_plat = 5.0;
   const float hi = 10.0;

   if (voltage < lo) return 1.0;
   if (voltage > hi) return 0.0;

   return plateauProfile( voltage, lo, lo_plat, hi_plat, hi );
}

fuzzyType mVoltageMedium(float voltage)
{
   const float lo = 5.0;
   const float lo_plat = 10.0;
   const float hi_plat = 20.0;
   const float hi = 25.0;

   if (voltage < lo) return 0.0;
   if (voltage > hi) return 0.0;

   return plateauProfile( voltage, lo, lo_plat, hi_plat, hi );
}

fuzzyType mVoltageHigh(float voltage)
{
   const float lo = 25.0;
   const float lo_plat = 30.0;
   const float hi_plat = 30.0;
   const float hi = 30.0;

   if (voltage < lo) return 0.0;
   if (voltage > hi) return 1.0;

   return plateauProfile( voltage, lo, lo_plat, hi_plat, hi );
}
