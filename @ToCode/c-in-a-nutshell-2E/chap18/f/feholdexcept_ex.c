// feholdexcept_ex.c : feholdexcept() example
// -------------------------------------------------------------

#include <fenv.h>     // int feholdexcept( fenv_t *envp );
#include <math.h>
#include <float.h>

/*
 * Compute the hypotenuse of a right triangle, avoiding intermediate
 * overflow or underflow.
 *
 * (This example ignores the case of one argument having
 * great magnitude and the other small, causing both overflow
 * and underflow!)
 */
double hypotenuse(double sidea, double sideb)
{
#pragma STDC FENV_ACCESS ON
    double sum, scale, ascaled, bscaled, invscale;
    fenv_t fpenv;
    int fpeflags;

    if ( signbit(sidea))  sidea = fabs(sidea);
    if ( signbit(sideb))  sideb = fabs(sideb);

    feholdexcept(&fpenv);        // Save previous environment,
                                 // clear exceptions,
                                 // switch to nonstop processing.
    invscale = 1.0;
    sum = sidea * sidea + sideb * sideb;    // First try whether a^2 + b^2
                                            // causes any exceptions.

    fpeflags = fetestexcept(FE_UNDERFLOW | FE_OVERFLOW);    // Did it?
    if (fpeflags & FE_OVERFLOW && sidea > 1.0 && sideb > 1.0)
    {
        /* a^2 + b^2 caused an overflow. Scale the triangle down. */
        feclearexcept(FE_OVERFLOW);
        scale = scalbn( 1.0, (DBL_MIN_EXP / 2));

        invscale = 1.0 / scale;
        ascaled = scale * sidea;
        bscaled = scale * sideb;
        sum = ascaled * ascaled + bscaled * bscaled;
    }
    else if (fpeflags & FE_UNDERFLOW && sidea < 1.0 && sideb < 1.0)
    {
        /* a^2 + b^2 caused an underflow. Scale the triangle up. */
        feclearexcept(FE_UNDERFLOW);
        scale = scalbn( 1.0, (DBL_MAX_EXP / 2));

        invscale = 1.0 / scale;
        ascaled = scale * sidea;
        bscaled = scale * sideb;
        sum = ascaled * ascaled + bscaled * bscaled;
    }

    feupdateenv(&fpenv);     // restore the caller's environment, and
                             // raise any new exceptions

    /* c = (1/scale) * sqrt((a * scale)^2 + (b * scale)^2): */
    return invscale * sqrt(sum);
}

#include <stdio.h>

int main()
{
    double sidec = hypotenuse( 1E-10, 2E-200);
    printf("The hypotenuse of the right triangle is %.10lG\n", sidec);

    return 0;
}
