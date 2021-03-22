#include "HasDma.h"

// hasDMA methods
HasDma::HasDma(const char* style, const char* label, int rating)
   : DmaBase(label, rating)
{
   const size_t len = strlen(style);
   style_ = new char[len + 1];
   strcpy_s(style_, len, style);
}

HasDma::HasDma(const char* style, const DmaBase& baseDma)
   : DmaBase(baseDma)
{
   const size_t len = strlen(style);
   style_ = new char[len + 1];
   strcpy_s(style_, len, style);
}

HasDma::HasDma(const HasDma& hasDma)
   : DmaBase(hasDma) // invoke base class copy constructor
{
   const size_t len = strlen(hasDma.style_);
   style_ = new char[len + 1];
   strcpy_s(style_, len, hasDma.style_);
}

HasDma::~HasDma()
{
   delete[] style_;
}

HasDma& HasDma::operator=(const HasDma& hasDma)
{
   if (this == &hasDma)
   {
      return *this;
   }

   DmaBase::operator=(hasDma); // copy base portion
   delete[] style_; // prepare for new style
   const size_t len = strlen(hasDma.style_);
   style_ = new char[len + 1];
   strcpy_s(style_, len, hasDma.style_);

   return *this;
}

std::ostream& operator<<(std::ostream& oStream, const HasDma& hasDma)
{
   oStream << static_cast<const DmaBase&>(hasDma);
   oStream << "Style: " << hasDma.style_ << std::endl;
   return oStream;
}
