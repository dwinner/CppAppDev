#ifndef DEREFERENCEOPS_POINTER_HPP
#define DEREFERENCEOPS_POINTER_HPP


#include <utility>

template<typename T>
class Pointer
{
public:
   explicit Pointer(T *ptr) : ptr_{ptr}
   {}

   virtual ~Pointer()
   {
      reset();
   }

   // Disallow copy constructor and copy assignment.
   Pointer(const Pointer &src) = delete;

   Pointer &operator=(const Pointer &rhs) = delete;

   // Allow move construction.
   Pointer(Pointer &&src) noexcept:
       ptr_{std::exchange(src.ptr_, nullptr)}
   {
   }

   // Allow move assignment.
   Pointer &operator=(Pointer &&rhs) noexcept
   {
      if (this != &rhs)
      {
         reset();
         ptr_ = std::exchange(rhs.ptr_, nullptr);
      }

      return *this;
   }

   T &operator*()
   {
      return *ptr_;
   }

   const T &operator*() const
   {
      return *ptr_;
   }

   T *operator->()
   {
      return ptr_;
   }

   const T *operator->() const
   {
      return ptr_;
   }

private:
   void reset()
   {
      delete ptr_;
      ptr_ = nullptr;
   }

   T *ptr_{nullptr};
};


#endif //DEREFERENCEOPS_POINTER_HPP
