// Example 14-4. A ring buffer for the producer-consumer model

/* buffer.h
 * Declarations for a thread-safe buffer.
 */
#include <stdbool.h>
#include <threads.h>

typedef struct Buffer
{
    int *data;              // Pointer to the array of data.
    size_t size, count;     // Maximum and current numbers of elements.
    size_t tip, tail;       // tip = index of the next free spot.
    mtx_t mtx;              // A mutex and
    cnd_t cndPut, cndGet;   // two condition variables.
} Buffer;

bool bufInit( Buffer *bufPtr, size_t size );
void bufDestroy(Buffer *bufPtr);

bool bufPut(Buffer *bufPtr, int data);
bool bufGet(Buffer *bufPtr, int *dataPtr, int sec);
