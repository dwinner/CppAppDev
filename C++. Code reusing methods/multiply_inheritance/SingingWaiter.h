#ifndef MULTIPLY_INHERITANCE_SINGINGWAITER_H
#define MULTIPLY_INHERITANCE_SINGINGWAITER_H

#include "Singer.h"
#include "Waiter.h"

class SingingWaiter : public Singer, public Waiter
{
public:
   SingingWaiter()
   {
   }

   SingingWaiter(const std::string& fullName, long id, int panache = 0, int voiceType = other)
      : Worker(fullName, id),
        Singer(fullName, id, voiceType),
        Waiter(fullName, id, panache)
   {
   }

   SingingWaiter(const Worker& worker, int panache = 0, int voiceType = other)
      : Worker(worker),
        Singer(worker, voiceType),
        Waiter(worker, panache)
   {
   }

   SingingWaiter(const Waiter& waiter, int voiceType = other)
      : Worker(waiter),
        Singer(waiter, voiceType),
        Waiter(waiter)
   {
   }

   SingingWaiter(const Singer& singer, int panache = 0)
      : Worker(singer),
        Singer(singer),
        Waiter(singer, panache)
   {
   }

   void set() override;

   void show() const override;

protected:
   void data() const override;

   void get() override;
};

#endif //MULTIPLY_INHERITANCE_SINGINGWAITER_H
