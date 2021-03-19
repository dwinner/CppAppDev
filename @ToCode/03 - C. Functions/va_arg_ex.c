// va_arg_ex.c : va_arg(), va_copy, va_end(), va_start() example
// -------------------------------------------------------------

#include <stdarg.h>  // void va_start( va_list argptr, last_fixed_arg );
                     // type va_arg( va_list argptr, type );
                     // void va_copy( va_list dest, va_list src );
                     // void va_end( va_list argptr );
#include <stdio.h>
#include <string.h>
#include <math.h>

double vproduct( int n, va_list argptr );
double vsum( int n, va_list argptr );

double vop( const char * op, int argcount, ... );

// main() calls vop() to perform calculations. vop()'s arguments are:
// (1) the name of the operation ("sum", "product",
//     "sum minus the product");
// (2) the number of operands;
// (3 through n) the operands themselves.
// Iterates through operations twice: once with three operands, once
// with six.

int main()
{
    double d1, d2, d3, d4, d5, d6;

    puts( "Enter six floating-point numbers, please:" );
    scanf( "%lf%lf%lf%lf%lf%lf", &d1, &d2, &d3, &d4, &d5, &d6 );

    char *operation[] = {"sum", "product", "product minus the sum",NULL};

    printf("\nUsing the three numbers %lf, %lf, and %lf.\n", d1, d2, d3);
    for ( int i = 0; operation[i] != NULL; i++ )
    {
        printf( "The %s of these %d numbers is %lf\n", 
                 operation[i], 3, vop( operation[i], 3, d1, d2, d3 ) );
    }

    printf( "\nUsing six numbers:"
            "\n\t%lf \t%lf \t%lf \n\t%lf \t%lf \t%lf\n",
            d1, d2, d3, d4, d5, d6 );
    for ( int i = 0; operation[i] != NULL; i++ )
    {
        printf( "The %s of these %d numbers is %lf\n",
                operation[i], 6, 
                vop( operation[i], 6, d1, d2, d3, d4, d5, d6 ) );
    }
}

double vop( const char * op, int argcount, ... )
{
    va_list argptr;
    double result;

    va_start( argptr, argcount );
    if ( strcmp( op, "sum" ) == 0 )
       result = vsum( argcount, argptr );
    else if ( strcmp( op, "product" ) == 0 )
       result = vproduct( argcount, argptr );
    else if ( strcmp( op, "product minus the sum" ) == 0 )
    {
       va_list duplicate_argptr;       // Clone the va_list in its present
                                       // state.
       va_copy( duplicate_argptr, argptr );
       result = vproduct( argcount, argptr )
                - vsum( argcount, duplicate_argptr );
       va_end( duplicate_argptr );     // Clean up the clone.
    }

    else result = NAN;

    va_end( argptr ); // Clean up the original.
    return result;
}

double vproduct( int n, va_list argptr )
{
    double product = 1.0;

    for ( int i = 0; i < n; i ++ )
        product *= va_arg( argptr, double );

    return product;
}

double vsum( int n, va_list argptr )
{
    double sum = 0.0;

    for ( int i = 0; i < n; i ++ )
        sum += va_arg( argptr, double );

    return sum;
}
