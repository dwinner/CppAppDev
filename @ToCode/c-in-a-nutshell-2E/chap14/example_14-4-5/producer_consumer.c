// Example 14-5. Starting the producer and consumer threads
// producer_consumer.c

#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>

#define NP 2                  // Number of producers
#define NC 3                  // Number of consumers

int producer(void *);         // The thread functions.
int consumer(void *);

struct Arg { int id; Buffer *bufPtr; };  // Arguments for the
                                         // thread functions.

_Noreturn void errorExit(const char* msg)
{
    fprintf(stderr, "%s\n", msg); exit(0xff);
}

int main(void)
{
    printf("Producer-Consumer Demo\n\n");
    Buffer buf;                           // Create a buffer for
    bufInit( &buf, 5 );                   // five products.

    thrd_t prod[NP], cons[NC];            // The threads and
    struct Arg prodArg[NP], consArg[NC];  // their arguments.
    int i = 0, res = 0;

    for ( i = 0; i < NP; ++i )            // Start the producers.
    {
       prodArg[i].id = i+1, prodArg[i].bufPtr = &buf;
       if ( thrd_create( &prod[i], producer, &prodArg[i] ) != thrd_success)
          errorExit("Thread error.");
    }

    for ( i = 0; i < NC; ++i )            // Start the consumers.
    {
       consArg[i].id = i+1, consArg[i].bufPtr = &buf;
       if ( thrd_create( &cons[i], consumer, &consArg[i] ) != thrd_success)
          errorExit("Thread error.");
    }

    for ( i = 0; i < NP; ++i )            // Wait for the threads to finish.
       thrd_join(prod[i], &res),
       printf("\nProducer %d ended with result %d.\n", prodArg[i].id, res);

    for ( i = 0; i < NC; ++i )
       thrd_join(cons[i], &res),
       printf("Consumer %d ended with result %d.\n", consArg[i].id, res);

    bufDestroy( &buf );
    return 0;
}

int producer(void *arg)             // The producers' thread function.
{
    struct Arg *argPtr = (struct Arg *)arg;
    int id = argPtr->id;
    Buffer *bufPtr = argPtr->bufPtr;

    int count = 0;
    for (int i = 0; i < 10; ++i)
    {
       int data = 10*id + i;
       if (bufPut( bufPtr, data ))
          printf("Producer %d produced %d\n", id, data), ++count;
       else
       { 
          fprintf( stderr, "Producer %d: error storing %d\n", id, data);
          return -id;
       }
    }
    return count;
}

int consumer(void *arg)             // The consumers' thread function.
{
    struct Arg *argPtr = (struct Arg *)arg;
    int id = argPtr->id;
    Buffer *bufPtr = argPtr->bufPtr;

    int count = 0;
    int data = 0;
    while (bufGet( bufPtr, &data, 2 ))
    {
       ++count;
       printf("Consumer %d consumed %d\n", id, data);
    }
    return count;
}
