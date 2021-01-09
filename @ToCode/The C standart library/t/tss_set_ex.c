// tss_set_ex.c : tss_set() example
// -------------------------------------------------------------

#include <threads.h>  // int tss_set(tss_t *key, void * ptr);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tss_t key;               // Global key for a TSS pointer
                         // tss_create(&key, ...) has been called.

typedef char Data_t;

size_t size_data( Data_t *dPtr)
{
    size_t size = strlen( dPtr) + 1;
    return size;
}

// Process some data of some type Data_t:
int process_data(void)   // Use thread-specific storage.
{
    Data_t *ptr = (Data_t*)tss_get(key); // Pointer to TSS

    puts("Process data ...");
    puts( ptr);
    return 0;
}

int thread_func( void* arg)
{
    size_t size = size_data( arg);   // A helper function to find the
                                     // required storage size.
    // Set thread-specific storage:
    if( tss_set(key, malloc(size)) != thrd_success)
       return -1;

    // Store and process data ...
    memcpy( tss_get(key), arg, size);
    return process_data();           // return calls the destructor, if
}                                    // the tss_create() call set one.

void destructor(void *data)
{
    printf("Destructor for %s\n", (char*)data);
    free(data);                    // Release memory.
}

int main(void)
{
    thrd_t th1, th2;
    int result1 = 0, result2 = 0;

    // Create the TSS key:
    if (tss_create(&key, destructor) != thrd_success)
       return -2;

    // Create threads:
    if ( thrd_create(&th1, thread_func, "Thread_1 ... ")
                                           != thrd_success
         || thrd_create(&th2, thread_func, "... Thread_2 ")
                                           != thrd_success )
       return -3;

    thrd_join( th1, &result1);
    thrd_join( th2, &result2);
    if ( result1 != 0 || result2 != 0)
       fputs("Thread error\n", stderr);
    else
       puts("Threads finished without error.");

    tss_delete(key); // Free all resources of the TSS pointer.
    return 0;
}
