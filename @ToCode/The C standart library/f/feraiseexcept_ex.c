// feraiseexcept_ex.c : feraiseexcept() example
// -------------------------------------------------------------

#include <fenv.h>     // int feraiseexcept( int excepts );
//#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Although user programs rarely need to raise a floating-point exception by artificial
// means, the following example illustrates how to do so:

int main()
{
    int result, except_set, except_test;

    #pragma STDC FENV_ACCESS ON

    feclearexcept (FE_ALL_EXCEPT);

    except_set = FE_OVERFLOW;
    result = feraiseexcept( except_set );
    if ( result != 0 )
    {
        printf( "feraisexcept() failed (%d)\n", result );
        exit( result );
    }

    except_test = fetestexcept( except_set );
    if ( except_test != except_set )
        printf( "Tried to raise flags %X, but only raised flags %X.\n",
                 except_set, except_test );
    else
       printf( "Raised the floating-point exception FE_ALL_EXCEPT = %X\n",
                except_set );       
    return 0;
}
