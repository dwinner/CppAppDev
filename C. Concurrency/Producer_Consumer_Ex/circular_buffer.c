#include <stdlib.h>
#include "circular_buffer.h"

bool buf_init(buffer_t* buf_ptr, size_t size)
{
   if ((buf_ptr->data = malloc(size * sizeof(int))) == NULL)
   {
      return false;
   }

   buf_ptr->size = size;
   buf_ptr->count = 0;
   buf_ptr->tip = buf_ptr->tail = 0;

   return mtx_init(&buf_ptr->mtx, mtx_plain) == thrd_success
      && cnd_init(&buf_ptr->cnd_put) == thrd_success
      && cnd_init(&buf_ptr->cnd_get) == thrd_success;
}

void buf_destroy(buffer_t* buf_ptr)
{
   cnd_destroy(&buf_ptr->cnd_get);
   cnd_destroy(&buf_ptr->cnd_put);
   mtx_destroy(&buf_ptr->mtx);
   free(buf_ptr->data);
}

bool buf_put(buffer_t* buf_ptr, int data)
{
   mtx_lock(&buf_ptr->mtx);

   // while the buffer_t is full
   while (buf_ptr->count == buf_ptr->size)
   {
      // waiting for consumer to set put-condition
      if (cnd_wait(&buf_ptr->cnd_put, &buf_ptr->mtx) != thrd_success)
      {
         return false;
      }
   }

   buf_ptr->data[buf_ptr->tip] = data;
   buf_ptr->tip = (buf_ptr->tip + 1) % buf_ptr->size;
   ++buf_ptr->count;

   mtx_unlock(&buf_ptr->mtx);
   cnd_signal(&buf_ptr->cnd_get);

   return true;
}

bool buf_get(buffer_t* buf_ptr, int* data_ptr, int sec)
{
   xtime time_out;
   time_out.sec = 1; // The current time + sec seconds delay.   

   mtx_lock(&buf_ptr->mtx);

   // while the buffer_t is full
   while (buf_ptr->count == 0)
   {
      // waiting for producer to set get-condition with timeout
      if (cnd_timedwait(&buf_ptr->cnd_get, &buf_ptr->mtx, &time_out) != thrd_success)
      {
         return false;
      }
   }

   *data_ptr = buf_ptr->data[buf_ptr->tail];
   buf_ptr->tail = (buf_ptr->tail + 1) % buf_ptr->size;
   --buf_ptr->count;

   mtx_unlock(&buf_ptr->mtx);
   cnd_signal(&buf_ptr->cnd_put);

   return true;
}
