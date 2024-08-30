/**
 * Starting the producer and consumer threads
 */

#include "circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Number of producers
 */
#define PRODUCER_NUMBER 2

/**
 * Number of consumers
 */
#define CONSUMER_NUMBER 3

// The thread functions.
int producer(void *);

int consumer(void *);

/**
 * Arguments for the thread functions.
 */
typedef struct
{
   int id;
   BufferT *bufPtr;
} ArgT;

_Noreturn void errorExit(const char *msg)
{
   fprintf(stderr, "%s\n", msg);
   exit(0xff);
}

int main(void)
{
   printf("Producer-Consumer Demo\n\n");

   // Create a buffer for five products.
   BufferT buf;
   buf_init(&buf, 5);

   // The threads and their arguments.
   thrd_t
       producerThr[PRODUCER_NUMBER],
       consumerThr[CONSUMER_NUMBER];
   ArgT
       prodArg[PRODUCER_NUMBER],
       consArg[CONSUMER_NUMBER];

   int i, res = 0;

   // Start the producers.
   for (i = 0; i < PRODUCER_NUMBER; ++i)
   {
      prodArg[i].id = i + 1, prodArg[i].bufPtr = &buf;
      if (thrd_create(&producerThr[i], producer, &prodArg[i]) != thrd_success)
      {
         errorExit("Thread error.");
      }
   }

   // Start the consumers.
   for (i = 0; i < CONSUMER_NUMBER; ++i)
   {
      consArg[i].id = i + 1, consArg[i].bufPtr = &buf;
      if (thrd_create(&consumerThr[i], consumer, &consArg[i]) != thrd_success)
      {
         errorExit("Thread error.");
      }
   }

   // Waiting for the threads to finish.
   for (i = 0; i < PRODUCER_NUMBER; ++i)
   {
      thrd_join(producerThr[i], &res),
          printf("\nProducer %d ended with result %d.\n", prodArg[i].id, res);
   }

   for (i = 0; i < CONSUMER_NUMBER; ++i)
   {
      thrd_join(consumerThr[i], &res),
          printf("Consumer %d ended with result %d.\n", consArg[i].id, res);
   }

   buf_destroy(&buf);

   return EXIT_SUCCESS;
}

int producer(void *arg)             // The producers' thread function.
{
   ArgT *argPtr = (ArgT *) arg;
   int id = argPtr->id;
   BufferT *bufPtr = argPtr->bufPtr;

   int count = 0;
   for (int i = 0; i < 10; ++i)
   {
      int data = 10 * id + i;
      if (buf_put(bufPtr, data))
      {
         printf("Producer %d produced %d\n", id, data), ++count;
      }
      else
      {
         fprintf(stderr, "Producer %d: error storing %d\n", id, data);
         return -id;
      }
   }

   return count;
}

int consumer(void *arg)             // The consumers' thread function.
{
   ArgT *argPtr = (ArgT *) arg;
   int id = argPtr->id;
   BufferT *bufPtr = argPtr->bufPtr;

   int count = 0;
   int data = 0;
   while (buf_get(bufPtr, &data, 2))
   {
      ++count;
      printf("Consumer %d consumed %d\n", id, data);
   }

   return count;
}
