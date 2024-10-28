#pragma once

#include <string>
#include <iostream>

/**
 * @brief Sample Error class with just a priority and a string error description.
 */
class Error final
{
public:
   explicit Error(int priority, std::string errorString) :
       priority_{priority},
       errorString_{std::move(errorString)}
   {
   }

   int getPriority() const
   {
      return priority_;
   }

   const std::string &getErrorString() const
   {
      return errorString_;
   }

   // Compare Errors according to their priority.
   auto operator<=>(const Error &rhs) const
   {
      return getPriority() <=> rhs.getPriority();
   }

private:
   int priority_;
   std::string errorString_;
};

// Stream insertion overload for Errors.
std::ostream &operator<<(std::ostream &os, const Error &err)
{
   std::print(os, "{} (priority {})", err.getErrorString(), err.getPriority());
   return os;
}
