#ifndef DYN_MEMORY_ALLOC_LACKSDMA_H
#define DYN_MEMORY_ALLOC_LACKSDMA_H

#include <iostream>
#include "DmaBase.h"

/**
 * derived class without DMA
 * no destructor needed
 * uses implicit copy constructor
 * uses implicit assignment operator
 */
class LacksDma : public DmaBase
{
public:
   explicit LacksDma(const char* color = "blank", const char* label = "null", int rating = 0);

   LacksDma(const char* color, const DmaBase& baseDma);

   friend std::ostream& operator<<(std::ostream& oStream, const LacksDma& lacksDma);
private:
   enum
   {
      col_len = 40
   };

   char color_[col_len];
};


#endif //DYN_MEMORY_ALLOC_LACKSDMA_H
