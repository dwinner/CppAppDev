// thrd_detach_ex.c : thrd_detach() example
// -------------------------------------------------------------

#include <threads.h>  // int thrd_detach( thrd_t thr);
#include <stdio.h>

void independent_thread(void)
{
   puts("Working independently in the background ... ");
   // . . .
   thrd_exit(0);
}

int create_independent_thread(void)
{
   thrd_t th;
   if (thrd_create(&th, (thrd_start_t) independent_thread, "") != thrd_success)
   {
      return -1;
   }

   if (thrd_detach(th) != thrd_success)
   {
      return -1;
   }

   puts("Started independent thread.");
   return 0;
}

int main()
{
   create_independent_thread();

   puts("Main thread here ...");

   // Working ...
   struct timespec d = {.tv_nsec = 1E6};  // 1 ms.
   thrd_sleep(&d, NULL);

   puts("Main thread done.");
   return 0;
}
