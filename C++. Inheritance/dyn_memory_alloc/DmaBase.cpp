#include "DmaBase.h"
#include <cstring>

DmaBase::DmaBase(const char* label, int rating)
{
   const size_t len = strlen(label);
   label_ = new char[len + 1];
   strcpy_s(label_, len, label);
   rating_ = rating;
}

DmaBase::DmaBase(const DmaBase& baseDma)
{
   const size_t len = strlen(baseDma.label_);
   label_ = new char[len + 1];
   strcpy_s(label_, len, baseDma.label_);
   rating_ = baseDma.rating_;
}

DmaBase::~DmaBase()
{
   delete[] label_;
}

DmaBase& DmaBase::operator=(const DmaBase& baseDma)
{
   if (this == &baseDma)
   {
      return *this;
   }

   delete[] label_;

   const size_t len = strlen(baseDma.label_);
   label_ = new char[len + 1];
   strcpy_s(label_, len, baseDma.label_);
   rating_ = baseDma.rating_;

   return *this;
}

std::ostream& operator<<(std::ostream& oStream, const DmaBase& baseDma)
{
   oStream << "Label: " << baseDma.label_ << std::endl;
   oStream << "Rating: " << baseDma.rating_ << std::endl;

   return oStream;
}
