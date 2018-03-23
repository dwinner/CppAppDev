// Fig. E.8: figE_08.c
// Using complex numbers in C99
#include <stdio.h>
#include <complex.h> // for complex type and math functions

int main()
{
    double complex a = 32.123 + 24.456 * I; // a is 32.123 + 24.456i
    double complex b = 23.789 + 42.987 * I; // b is 23.789 + 42.987i
    double complex c = 3 + 2 * I; // c is 3.0 + 2.0i

    double complex sum = a + b; // perform complex addition
    double complex pwr = cpow(a, c); // perform complex exponentiation

    printf("a is %f + %fi\n", creal(a), cimag(a));
    printf("b is %f + %fi\n", creal(b), cimag(b));
    printf("a + b is: %f + %fi\n", creal(sum), cimag(sum));
    printf("a - b is: %f + %fi\n", creal(a - b), cimag(a - b));
    printf("a * b is: %f + %fi\n", creal(a * b), cimag(a * b));
    printf("a / b is: %f + %fi\n", creal(a / b), cimag(a / b));
    printf("a ^ b is: %f + %fi\n", creal(pwr), cimag(pwr));
} 
