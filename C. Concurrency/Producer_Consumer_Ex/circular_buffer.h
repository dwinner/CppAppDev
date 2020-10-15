#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <thr/threads.h>

/**
 * \brief A ring buffer_t for the producer-consumer model
 */
typedef struct buffer
{
   /**
    * \brief Pointer to the array of data
    */
   int* data;

   /**
    * \brief Maximum number of elements
    */
   size_t size;

   /**
    * \brief Current number of elements
    */
   size_t count;

   /**
    * \brief Index of the next free spot
    */
   size_t tip;

   /**
    * \brief tail index of the buffer_t
    */
   size_t tail;

   /**
    * \brief Mutex for prod-cons model
    */
   mtx_t mtx;

   /**
    * \brief Condition variable for put-operations
    */
   cnd_t cnd_put;

   /**
    * \brief Condition variable for get-operations
    */
   cnd_t cnd_get;
} buffer_t;

/**
 * \brief Buffer init
 * \param buf_ptr Pointer to the buffer_t
 * \param size size of the buffer_t's data
 * \return true if init is successful, false - otherwise
 */
bool buf_init(buffer_t* buf_ptr, size_t size);

/**
 * \brief Destroy the buffer_t and free allocated memory
 * \param buf_ptr Pointer to buffer_t
 */
void buf_destroy(buffer_t* buf_ptr);

/**
 * \brief Insert a new element in the buffer_t
 * \param buf_ptr Pointer to buffer_t
 * \param data Data to put
 * \return true if data has been put, false - otherwise
 */
bool buf_put(buffer_t* buf_ptr, int data);

/**
 * \brief Remove an element from the buffer_t
 * \details If the buffer_t is empty, wait no more than 'sec'-seconds
 * \param buf_ptr Pointer to buffer_t
 * \param data_ptr Pointer to data
 * \param sec Count of second to wait
 * \return true if consumer has got the data, false - otherwise
 */
bool buf_get(buffer_t* buf_ptr, int* data_ptr, int sec);

#endif // CIRCULAR_BUFFER_H
