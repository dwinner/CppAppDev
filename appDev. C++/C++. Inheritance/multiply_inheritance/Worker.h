#ifndef MULTIPLY_INHERITANCE_WORKER_H
#define MULTIPLY_INHERITANCE_WORKER_H

#include <string>

class Worker
{
public:
   Worker()
      : fullName_("no one"),
        id_(0L)
   {
   }

   Worker(const std::string& fullName, long id)
      : fullName_(fullName),
        id_(id)
   {
   }

   virtual ~Worker() = 0; // pure virtual function
   virtual void set() = 0;

   virtual void show() const = 0;

protected:
   virtual void data() const;

   virtual void get();

private:
   std::string fullName_;
   long id_;
};

#endif //MULTIPLY_INHERITANCE_WORKER_H
