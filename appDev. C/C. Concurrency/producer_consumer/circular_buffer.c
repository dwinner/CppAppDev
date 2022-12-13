#include "circular_buffer.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/**
 * @brief Produces the time out from the current time
 * @param delay Delay in seconds
 * @return Timeout in seconds
 */
static timespec_t make_timeout_sec(int delay);

bool buf_init(BufferT *buf_ptr, const size_t size)
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

void buf_destroy(BufferT *buf_ptr)
{
   cnd_destroy(&buf_ptr->cnd_get);
   cnd_destroy(&buf_ptr->cnd_put);
   mtx_destroy(&buf_ptr->mtx);
   free(buf_ptr->data);
}

bool buf_put(BufferT *buf_ptr, const int data, const int sec)
{
   // set the 'sec'-seconds time out from the current time
   timespec_t timeout = make_timeout_sec(sec);

   mtx_lock(&buf_ptr->mtx);

   // while the buffer_t is full
   while (buf_ptr->count == buf_ptr->size)
   {
      // waiting for consumer to set put-condition with timeout
      if (cnd_timedwait(&buf_ptr->cnd_put, &buf_ptr->mtx, &timeout) != thrd_success)
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

bool buf_get(BufferT *buf_ptr, int *data_ptr, const int sec)
{
   // set the 'sec'-seconds time out from the current time
   timespec_t timeout = make_timeout_sec(sec);

   mtx_lock(&buf_ptr->mtx);

   // while the buffer_t is full
   while (buf_ptr->count == 0)
   {
      // waiting for producer to set get-condition with timeout
      if (cnd_timedwait(&buf_ptr->cnd_get, &buf_ptr->mtx, &timeout) != thrd_success)
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

static timespec_t make_timeout_sec(const int delay)
{
   timespec_t time_out;
   clock_gettime(CLOCK_REALTIME, &time_out);
   time_out.tv_sec += delay;

   return time_out;
}
