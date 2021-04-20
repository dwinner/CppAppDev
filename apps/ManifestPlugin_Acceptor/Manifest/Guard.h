#pragma once

#include <functional>
#include <utility>

namespace manifest_reader
{
   class Guard
   {
   public:
      explicit Guard(std::function<void()> func)
         : func_(std::move(func))
           , isActive_(true)
      {
      }

      void Release()
      {
         isActive_ = false;
      }

      ~Guard()
      {
         if (isActive_)
         {
            func_();
         }
      }

   private:
      std::function<void()> func_;
      bool isActive_;
   };
}
