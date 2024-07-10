#ifndef DYN_MEMORY_ALLOC_DMABASE_H
#define DYN_MEMORY_ALLOC_DMABASE_H

#include <iostream>

class DmaBase
{
public:
   explicit DmaBase(const char* label = "null", int rating = 0);

   DmaBase(const DmaBase& baseDma);

   virtual ~DmaBase();

   DmaBase& operator=(const DmaBase& baseDma);

   friend std::ostream& operator<<(std::ostream& oStream, const DmaBase& baseDma);

private:
   char* label_;
   int rating_;
};

#endif //DYN_MEMORY_ALLOC_DMABASE_H
