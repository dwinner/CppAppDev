// wmemcpy_ex.c : wmemcpy(), wmemcpy_s() example
// -------------------------------------------------------------
// wchar_t *wmemcpy( wchar_t * restrict dest,
//                   const wchar_t * restrict src,
//                   size_t n );
// errno_t wmemcpy_s( wchar_t * restrict dest, rsize_t destmax,
//                    const wchar_t * restrict src,
//                    rsize_t n);

#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 2048     // Size as a number of wchar_t elements.

wchar_t inputbuffer[BUFFERSIZE] = {L'\0'},
    *writeptr = inputbuffer;

struct block
{
   wchar_t *text;
   struct block *next;
   struct block *prev;
} firstblock = {NULL},  // The first block is the list head.
*tmp = NULL;

struct block *newblock(struct block *lastblock);

// Creates a linked-list member.
wchar_t *storetext(struct block *listhead,
                   wchar_t *buffer,
                   size_t bufsize);
// Copies input buffer to a new linked-list member.

int main()
{
   while (fgetws(writeptr, BUFFERSIZE - (writeptr - inputbuffer), stdin) != NULL)
   {
      // Set writeptr to end of the input string:
      writeptr = wmemchr(inputbuffer, L'\0',
                         sizeof(inputbuffer) / sizeof(wchar_t));

      if (BUFFERSIZE - (writeptr - inputbuffer) < 80)
         // If block full, or nearly so:
      {                                    // copy buffer to a data block.
         writeptr = storetext(&firstblock, inputbuffer, BUFFERSIZE);
         if (writeptr == NULL)
         {          // Out of memory!
            abort();
         }
      }
   }    // Here if fgetws() returns NULL.

   writeptr = storetext(&firstblock, inputbuffer, BUFFERSIZE);
   if (writeptr == NULL)
   {                 // Out of memory!
      abort();
   }
}

// ----------------------------
wchar_t *storetext(struct block *listhead,
                   wchar_t *buffer, size_t bufsize)
// Copies input buffer to a new chained-list member;
// returns pointer to input buffer, or NULL on failure.
{
   struct block *tmp = listhead;     // create new block on end of list ...
   while (tmp->next != NULL)
   {
      tmp = tmp->next;
   }
   if ((tmp = newblock(tmp)) != NULL)
   {
      wmemcpy(tmp->text, buffer, bufsize);     // ... and copy the text.
      // Or:
      // wmemcpy_s( tmp->text, BUFFERSIZE, buffer, bufsize );
   }
   else
   {            // Out of memory!
      return NULL;
   }

#ifdef DEBUG
   fwprintf( stderr, L"\nStored a block with this text:\n%ls\n",
              tmp->text );
#endif

   return buffer;     // Return pointer to buffer, now ready for re-use.
}

// ----------------------------
// Allocates a new block and appends it to the chained list;
// returns pointer to new block, or NULL on failure.
struct block *newblock(struct block *lastblock)
{
   if ((lastblock->next = malloc(sizeof(struct block))) != NULL
       && (lastblock->next->text = malloc(BUFFERSIZE * sizeof(wchar_t))) != NULL)
   {
      lastblock->next->prev = lastblock;
      lastblock->next->next = NULL;
      return lastblock->next;
   }
   else
   {            // Out of memory!
      return NULL;
   }
}
