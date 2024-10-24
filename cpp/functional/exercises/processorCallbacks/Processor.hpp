#pragma once

#include <functional>

class Processor
{
public:
   explicit Processor(const std::function<int(int)> &delegate);

   int operator()(int inputValue) const;

   [[nodiscard]] inline const std::function<int(int)> &getDelegate() const;

   void setDelegate(const std::function<int(int)> &delegate);

private:
   std::function<int(int)> delegate_;
};
