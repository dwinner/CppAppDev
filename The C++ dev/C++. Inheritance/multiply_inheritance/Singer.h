#ifndef MULTIPLY_INHERITANCE_SINGER_H
#define MULTIPLY_INHERITANCE_SINGER_H

#include "Worker.h"

class Singer : virtual public Worker
{
public:
   Singer()
      : Worker(),
        voice_(other)
   {
   }

   Singer(const std::string& fullName, long id, int voiceType = other)
      : Worker(fullName, id),
        voice_(voiceType)
   {
   }

   Singer(const Worker& worker, int voiceType = other)
      : Worker(worker),
        voice_(voiceType)
   {
   }

   void set() override;

   void show() const override;

protected:
   enum
   {
      other,
      alto,
      contralto,
      soprano,
      bass,
      baritone,
      tenor
   };

   enum
   {
      vtypes = 7
   };

   void data() const override;

   void get() override;

private:
   static char* voiceTypes_[vtypes]; // string equivs of voice types
   int voice_;
};

#endif //MULTIPLY_INHERITANCE_SINGER_H
