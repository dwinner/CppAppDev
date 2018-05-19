// Example 14-7. Using thread-specific storage
// thread-specific_storage.c

#include <threads.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tss_t key;                 // Global key for a TSS pointer

int thFunc(void *arg);                 // Thread function
void destructor(void *data);           // Destructor function

int main(void)
{
    thrd_t th1, th2;
    int result1 = 0, result2 = 0;

    // Create the TSS key:
    if (tss_create(&key, destructor) != thrd_success)
       return -1;

    // Create threads:
    if (   thrd_create(&th1, thFunc, "Thread_1") != thrd_success
        || thrd_create(&th2, thFunc, "Thread_2") != thrd_success)
       return -2;

    thrd_join(th1, &result1); thrd_join(th2, &result2);
    if ( result1 != 0 || result2 != 0 )
       fputs("Thread error\n", stderr);
    else
       puts("Threads finished without error.");

    tss_delete(key); // Free all resources of the TSS pointer.
    return 0;
}

void print(void)                  // Display thread-specific storage.
{
    printf( "print: %s\n", (char*)tss_get(key) );
}

int thFunc( void *arg )           // Thread function
{
    char *name = (char*)arg;
    size_t size = strlen(name)+1;

    // Set thread-specific storage:
    if ( tss_set(key, malloc(size)) != thrd_success )
       return -1;
    // Store data:
    strcpy((char*)tss_get(key), name);
    print();
    return 0;
}

void destructor(void *data)
{
    printf("Destructor for %s\n", (char*)data);
    free(data);                    // Release memory.
}
