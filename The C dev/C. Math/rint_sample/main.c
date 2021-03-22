// rint_ex.c : rint() example
// -------------------------------------------------------------

#include <math.h>    // double rint( double x );
// float rintf( float x );
// long double rintl( long double x );
#include <fenv.h>
#include <stdio.h>

struct round_modes
{
   int id;
   char *str;
} arrModes[] =
    {
#ifdef FE_TONEAREST
        {
            FE_TONEAREST,
            "FE_TONEAREST: round to nearest representable value"
        },
#endif
#ifdef FE_DOWNWARD
        {FE_DOWNWARD, "FE_DOWNWARD: round toward -Inf"},
#endif
#ifdef FE_UPWARD
        {FE_UPWARD, "FE_UPWARD: round toward +Inf"},
#endif
#ifdef FE_TOWARDZERO
        {FE_TOWARDZERO, "FE_TOWARDZERO: round toward 0"}
#endif
    };

int main()
{
   int nModes = sizeof(arrModes) / sizeof(*arrModes);

#pragma STDC FENV_ACCESS ON

   for (int i = 0; i < nModes; ++i)
   {
      if (fesetround(arrModes[i].id) != 0)
      {
         break;
      }
      printf("Rounding mode: %s\n", arrModes[i].str);

      printf("rint(1.4)  = %4.1f    rint(1.5)  = %4.1f\n",
             rint(1.4), rint(1.5));
      printf("rint(-1.4) = %4.1f    rint(-1.5) = %4.1f\n",
             rint(-1.4), rint(-1.5));
   }

   return 0;
}
