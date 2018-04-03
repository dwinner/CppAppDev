// Fig. E.12: figE_12.c
// Fibonacci calculations performed in separate threads
#include <stdio.h>
#include <threads.h>
#include <time.h>

#define NUMBER_OF_THREADS 2

int startFibonacci(void *nPtr);
unsigned long long int fibonacci(unsigned int n); 

typedef struct ThreadData {
   time_t startTime; // time thread starts processing
   time_t endTime; // time thread finishes processing
   unsigned int number; // fibonacci number to calculate
} ThreadData; // end struct ThreadData

int main(void) 
{
   // data passed to the threads; uses designated initializers
   ThreadData data[NUMBER_OF_THREADS] = 
      {[0] = {.number = 50},   
       [1] = {.number = 49}};

   // each thread needs a thread identifier of type thrd_t
   thrd_t threads[NUMBER_OF_THREADS]; 

   puts("fibonacci(50) and fibonacci(49) in separate threads");

   // create and start the threads
   for (size_t i = 0; i < NUMBER_OF_THREADS; ++i) {
      printf("Starting thread to calculate fibonacci(%d)\n", 
         data[i].number);

      // create a thread and check whether creation was successful
      if (thrd_create(&threads[i], startFibonacci, &data[i]) !=
         thrd_success) {

         puts("Failed to create thread");
      } 
   } 

   // wait for each of the calculations to complete
   for (size_t i = 0; i < NUMBER_OF_THREADS; ++i)
      thrd_join(threads[i], NULL);

   // determine time that first thread started
   time_t startTime = (data[0].startTime < data[1].startTime) ? 
      data[0].startTime : data[1].startTime;

   // determine time that last thread terminated
   time_t endTime = (data[0].endTime > data[1].endTime) ? 
      data[0].endTime : data[1].endTime;

   // display total time for calculations
   printf("Total calculation time = %f minutes\n", 
      difftime(endTime, startTime) / 60.0);
} 

// Called by a thread to begin recursive Fibonacci calculation
int startFibonacci(void *ptr) 
{
   // cast ptr to ThreadData * so we can access arguments
   ThreadData *dataPtr = (ThreadData *) ptr;

   dataPtr->startTime = time(NULL); // time before calculation
 
   printf("Calculating fibonacci(%d)\n", dataPtr->number);
   printf("fibonacci(%d) = %lld\n", 
      dataPtr->number, fibonacci(dataPtr->number));

   dataPtr->endTime = time(NULL); // time after calculation
 
   printf("Calculation time = %f minutes\n\n", 
      difftime(dataPtr->endTime, dataPtr->startTime) / 60.0);
   return thrd_success; 
} 

// Recursively calculates fibonacci numbers
unsigned long long int fibonacci(unsigned int n)      
{                                                         
   // base case                                           
   if (0 == n || 1 == n) {                               
      return n;                                            
   }                                            
   else { // recursive step                            
      return fibonacci(n - 1) + fibonacci(n - 2);        
   }                                         
} 
