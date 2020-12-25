#ifndef MULTIPLY_INHERITANCE_WAITER_H
#define MULTIPLY_INHERITANCE_WAITER_H

#include "Worker.h"

class Waiter : virtual public Worker
{
public:
   Waiter()
      : Worker(),
        panache_(0)
   {
   }

   Waiter(const std::string& fullName, long id, int panache = 0)
      : Worker(fullName, id),
        panache_(panache)
   {
   }

   Waiter(const Worker& worker, int panache = 0)
      : Worker(worker),
        panache_(panache)
   {
   }

   void set() override;

   void show() const override;

protected:
   void data() const override;

   void get() override;

private:
   int panache_;
};


#endif //MULTIPLY_INHERITANCE_WAITER_H
