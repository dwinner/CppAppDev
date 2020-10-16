/**
 * Starting the producer and consumer threads
 */

#include "circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <thr/threads.h>

#define NP 2                  // Number of producers
#define NC 3                  // Number of consumers
#define TIME_OUT_SEC 2        // Timeout in seconds

// The thread functions.
int producer(void*);
int consumer(void*);

struct arg
{
   int id;
   BufferT* buf_ptr;
}; // Arguments for the thread functions.

_Noreturn void error_exit(const char* msg)
{
   fprintf(stderr, "%s\n", msg);
   exit(0xff);
}

int main()
{
   printf("Producer-Consumer Demo\n\n");
   BufferT buf; // Create a buffer for
   buf_init(&buf, 5); // five products.

   thrd_t prod[NP], cons[NC]; // The threads and
   struct arg prod_arg[NP], cons_arg[NC]; // their arguments.
   int i;
   int res = 0;

   for (i = 0; i < NP; ++i) // Start the producers.
   {
      prod_arg[i].id = i + 1,
         prod_arg[i].buf_ptr = &buf;
      if (thrd_create(&prod[i], producer, &prod_arg[i]) != thrd_success)
      {
         error_exit("Thread error.");
      }
   }

   for (i = 0; i < NC; ++i) // Start the consumers.
   {
      cons_arg[i].id = i + 1, cons_arg[i].buf_ptr = &buf;
      if (thrd_create(&cons[i], consumer, &cons_arg[i]) != thrd_success)
      {
         error_exit("Thread error.");
      }
   }

   for (i = 0; i < NP; ++i) // Wait for the threads to finish.
   {
      thrd_join(prod[i], &res),
         printf("\nProducer %d ended with result %d.\n", prod_arg[i].id, res);
   }

   for (i = 0; i < NC; ++i)
   {
      thrd_join(cons[i], &res),
         printf("Consumer %d ended with result %d.\n", cons_arg[i].id, res);
   }

   buf_destroy(&buf);

   return 0;
}

int producer(void* arg) // The producers' thread function.
{
   struct arg* arg_ptr = (struct arg*)arg;
   const int id = arg_ptr->id;
   BufferT* buf_ptr = arg_ptr->buf_ptr;

   int count = 0;
   for (int i = 0; i < 10; ++i)
   {
      const int data = 10 * id + i;
      if (buf_put(buf_ptr, data, TIME_OUT_SEC))
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

int consumer(void* arg) // The consumers' thread function.
{
   struct arg* arg_ptr = (struct arg*)arg;
   const int id = arg_ptr->id;
   BufferT* buf_ptr = arg_ptr->buf_ptr;

   int count = 0;
   int data = 0;
   while (buf_get(buf_ptr, &data, TIME_OUT_SEC))
   {
      ++count;
      printf("Consumer %d consumed %d\n", id, data);
   }

   return count;
}
