#ifndef DYN_MEMORY_ALLOC_HASDMA_H
#define DYN_MEMORY_ALLOC_HASDMA_H

#include <iostream>
#include "DmaBase.h"

class HasDma : public DmaBase
{
public:
   explicit HasDma(const char* style = "none", const char* label = "null", int rating = 0);

   HasDma(const char* style, const DmaBase& baseDma);

   HasDma(const HasDma& hasDma);

   ~HasDma();

   HasDma& operator=(const HasDma& hasDma);

   friend std::ostream& operator<<(std::ostream& oStream, const HasDma& hasDma);

private:
   char* style_;
};


#endif //DYN_MEMORY_ALLOC_HASDMA_H
