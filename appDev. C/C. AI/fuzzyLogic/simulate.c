#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "simulate.h"

static int curLoad = 0;
int chargeMode = TRICKLE_CHARGE;
float voltage = 20.0F;
float temperature = 12.0F;
float timer = 0.0F;
const float load[MAX_LOADS] =
    {
        0.02F,
        0.04F,
        0.06F,
        0.08F,
        0.1F
    };

void chargeControl(float *aTimer)
{
   static unsigned int i = 0;

   if ((i++ % 10) == 0)
   {
      if (normalize(mVoltageHigh(voltage)) || normalize(mTempHot(temperature)))
      {
         chargeMode = TRICKLE_CHARGE;
         *aTimer = 0.0F;
      }
      else if (normalize(
          fuzzyAnd(fuzzyNot(mVoltageHigh(voltage)),
                   fuzzyNot(mTempHot(temperature)))))
      {
         chargeMode = FAST_CHARGE;
         *aTimer = 0.0F;
      }
   }

   printf("%d, %f, %f %d\n", i, voltage, temperature, chargeMode);
}

double charge(int aTemperature)
{
   double result;
   result = sin((double) aTemperature / 100.0);
   if (result < 0.0)
   {
      result = 0.0;
   }

   return result;
}

int simulate(void)
{
   static int sTemp = 0;

   /* First, update the loading if necessary */
   if (getSRand() < 0.02)
   {
      curLoad = getRand(MAX_LOADS);
   }

   /* Affect the current battery voltage given the load */
   voltage -= load[curLoad];

   /* Next, update the battery voltage given input charge */
   if (chargeMode == FAST_CHARGE)
   {
      voltage += (float) (charge(sTemp) * sqrtf(timer));
   }
   else
   {
      voltage += (float) ((charge(sTemp) * sqrtf(timer)) / 10.0);
   }

   if (voltage < 0.0)
   {
      voltage = 0.0F;
   }
   else if (voltage > 35.0)
   {
      voltage = 35.0F;
   }

   /* Update the temperature */
   if (chargeMode == FAST_CHARGE)
   {
      if (voltage > 25)
      {
         temperature += (float) ((load[curLoad] * (sqrtf(timer) / 25.0)) * 10.0);
      }
      else if (voltage > 15)
      {
         temperature += (float) ((load[curLoad] * (sqrtf(timer) / 20.0)) * 10.0);
      }
      else
      {
         temperature += (float) ((load[curLoad] * (sqrtf(timer) / 15.0)) * 10.0);
      }
   }
   else
   {
      if (temperature > 20.0)
      {
         temperature -= (float) ((load[curLoad] * (sqrtf(timer) / 20.0)) * 10.0);
      }
      else
      {
         temperature -= (float) ((load[curLoad] * (sqrtf(timer) / 100.0)) * 10.0);
      }
   }

   if (temperature < 0.0)
   {
      temperature = 0.0F;
   }
   else if (temperature > 40.0)
   {
      temperature = 40.0F;
   }

   sTemp++;

   return 0;
}

#pragma clang diagnostic pop