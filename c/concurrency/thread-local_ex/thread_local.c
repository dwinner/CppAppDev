// Example 14-6. Using a thread-local object
// thread-local.c

#include <stdio.h>
#include <threads.h>

_Thread_local int var = 10;

void print_var(void)
{
   printf("var = %d\n", var);
}

int func(void *); // Thread function

int main(int argc, char *argv[])
{
   thrd_t th1;
   if (thrd_create(&th1, func, NULL) != thrd_success)
   {
      fprintf(stderr, "Error creating thread.\n");
      return 0xff;
   }

   print_var(); // Output: var = 10
   thrd_join(th1, NULL);

   return 0;
}

int func(void *arg) // Thread function
{
   var += 10; // Thread-local variable
   print_var(); // Output: var = 20
   return 0;
}
