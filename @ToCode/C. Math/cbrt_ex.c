// cbrt_ex.c : cbrt() example
// -------------------------------------------------------------

#include <math.h>     // double cbrt( double x );
                      // float cbrtf( float x );
                      // long double cbrtl( long double x );
#include <stdio.h>

#define KM_PER_AU (149597870.691)   // An astronomical unit is the mean
                                    // distance between Earth and Sun:
                                    // about 150 million km.
#define DY_PER_YR (365.24)

int main()
{
    double dist_au, dist_km, period_dy, period_yr;

    printf("How long is a solar year on your planet (in Earth days)?\n");
    scanf( "%lf", &period_dy );

    period_yr = period_dy / DY_PER_YR;
    dist_au = cbrt( period_yr * period_yr );     // by Kepler's Third Law
    dist_km = dist_au * KM_PER_AU;

    printf("Then your planet must be about %.0lf km from the Sun.\n",
                                                             dist_km );
    return 0;
}
