#include "LacksDma.h"

LacksDma::LacksDma(const char* color, const char* label, int rating)
   : DmaBase(label, rating)
{
   const int len = col_len - 1;
   strncpy_s(color_, color, len);
   color_[len] = '\0';
}

LacksDma::LacksDma(const char* color, const DmaBase& baseDma)
   : DmaBase(baseDma)
{
   strncpy_s(color_, color, col_len - 1);
   color_[col_len - 1] = '\0';
}

std::ostream& operator<<(std::ostream& oStream, const LacksDma& lacksDma)
{
   oStream << static_cast<const DmaBase&>(lacksDma);
   oStream << "Color: " << lacksDma.color_ << std::endl;
   return oStream;
}
