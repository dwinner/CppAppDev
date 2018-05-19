// main.c : 
// Calls the function sum() which calls the recursive helper function parallel_sum().

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool sum( float arr[], int len, double* sumPtr);

#define ARRSIZE 1000000
float arr[ARRSIZE];

int main(int argc, char *argv[])
{
    double arr_sum = 0;

    for( int i = 0; i < ARRSIZE; ++i)
       arr[i] = i/10.0;

	clock_t t1 = clock();
    if( !sum( arr, ARRSIZE, &arr_sum))
    {
       fprintf( stderr, "Error in executing sum()\n");
       return -1;
    }
	clock_t t2 = clock();
    printf("CPU time used: %ld milliseconds.\n", (t2-t1)*1000/CLOCKS_PER_SEC);

    printf("The sum %.1f + %.1f + ... + %.1f = %.1lf\n", 
		        arr[0], arr[1], arr[ARRSIZE-1], arr_sum);
    printf("The correct sum is: %lld\n", (long long)ARRSIZE*(ARRSIZE-1)/20);

    printf("main() terminated.\n");
    return 0;
}

