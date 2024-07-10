#include "mbrship.h"

int normalize(FuzzyBoolT in)
{
   return in >= 0.5 ? 1 : 0;
}

FuzzyBoolT spikeProfile(float value, float lo, float high)
{
   float peak;
   value += (-lo);

   if ((lo < 0) && (high < 0))
   {
      high = -(high - lo);
   }
   else if ((lo < 0) && (high > 0))
   {
      high += -lo;
   }
   else if ((lo > 0) && (high > 0))
   {
      high -= lo;
   }

   peak = (float) (high / 2.0);
   if (value < peak)
   {
      return (value / peak);
   }
   else if (value > peak)
   {
      return ((high - value) / peak);
   }

   return 1.0F;
}

FuzzyBoolT plateauProfile(float value, float lo, float loPlat, float hiPlat, float hi)
{
   float upSlope;
   float downSlope;
   value += (-lo);

   if (lo < 0.0)
   {
      loPlat += -lo;
      hiPlat += -lo;
      hi += -lo;
      lo = 0;
   }
   else
   {
      loPlat -= lo;
      hiPlat -= lo;
      hi -= lo;
      lo = 0;
   }

   upSlope = (float) (1.0 / (loPlat - lo));
   downSlope = (float) (1.0 / (hi - hiPlat));
   if (value < lo || value > hi)
   {
      return 0.0F;
   }
   else if ((value >= loPlat) && (value <= hiPlat))
   {
      return 1.0F;
   }
   else if (value < loPlat)
   {
      return ((value - lo) * upSlope);
   }
   else if (value > hiPlat)
   {
      return ((hi - value) * downSlope);
   }

   return 0.0F;
}

FuzzyBoolT mTempHot(float temperature)
{
   const float lo = 35.0F;
   const float loPlat = 45.0F;
   const float hiPlat = 45.0F;
   const float hi = 45.0F;

   if (temperature < lo)
   {
      return 0.0F;
   }

   if (temperature > hi)
   {
      return 1.0F;
   }

   return plateauProfile(temperature, lo, loPlat, hiPlat, hi);
}

FuzzyBoolT mTempWarm(float aTemperature)
{
   const float lo = 15.0F;
   const float loPlat = 25.0F;
   const float hiPlat = 35.0F;
   const float hi = 45.0F;

   if ((aTemperature < lo) || (aTemperature > hi))
   {
      return 0.0F;
   }

   return plateauProfile(aTemperature, lo, loPlat, hiPlat, hi);
}

FuzzyBoolT mTempCold(float temperature)
{
   const float lo = 15.0F;
   const float loPlat = 15.0F;
   const float hiPlat = 15.0F;
   const float hi = 25.0F;

   if (temperature < lo)
   {
      return 1.0F;
   }

   if (temperature > hi)
   {
      return 0.0F;
   }

   return plateauProfile(temperature, lo, loPlat, hiPlat, hi);
}

FuzzyBoolT mVoltageLow(float voltage)
{
   const float lo = 5.0F;
   const float loPlat = 5.0F;
   const float hiPlat = 5.0F;
   const float hi = 10.0F;

   if (voltage < lo)
   {
      return 1.0F;
   }

   if (voltage > hi)
   {
      return 0.0F;
   }

   return plateauProfile(voltage, lo, loPlat, hiPlat, hi);
}

FuzzyBoolT mVoltageMedium(float voltage)
{
   const float lo = 5.0F;
   const float lo_plat = 10.0F;
   const float hi_plat = 20.0F;
   const float hi = 25.0F;

   if (voltage < lo)
   {
      return 0.0F;
   }

   if (voltage > hi)
   {
      return 0.0F;
   }

   return plateauProfile(voltage, lo, lo_plat, hi_plat, hi);
}

FuzzyBoolT mVoltageHigh(float voltage)
{
   const float lo = 25.0F;
   const float lo_plat = 30.0F;
   const float hi_plat = 30.0F;
   const float hi = 30.0F;

   if (voltage < lo)
   {
      return 0.0F;
   }

   if (voltage > hi)
   {
      return 1.0F;
   }

   return plateauProfile(voltage, lo, lo_plat, hi_plat, hi);
}
