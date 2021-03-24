// fmod_ex.c : fmod() example
// -------------------------------------------------------------
// double fmod( double x, double y );
// float fmodf( float x, float y );
// long double fmodl( long double x, long double y );

#include <math.h>
#include <fenv.h>
#include <stdio.h>

int main()
{
   double people = -2.25,
       apples = 3.3,
       eachgets = 0.0,
       someleft = 0.0;

   // Save previous setting
   int saverounding = fegetround();
   fesetround(FE_TOWARDZERO);

   eachgets = rint(apples / people);
   someleft = fmod(apples, people);

   printf("If there are %+.2f of us and %+.2f apples, \n"
          "each of us gets %+.2f, with %+.2f left over.\n",
          people, apples, eachgets, someleft);

   // Restore previous setting
   fesetround(saverounding);

   return 0;
}
