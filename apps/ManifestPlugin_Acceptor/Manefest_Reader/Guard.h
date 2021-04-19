#pragma once

#include <functional>

namespace manifest_reader
{
   class Guard
   {
   public:
      Guard(const std::function<void()>& func)
         : func_(func)
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
