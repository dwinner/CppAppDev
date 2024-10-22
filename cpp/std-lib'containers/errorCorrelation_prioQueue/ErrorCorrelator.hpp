#pragma once

#include <queue>
#include "Error.hpp"

/**
 * @brief Simple Error correlation class that returns the highest priority errors first.
 */
class ErrorCorrelator final
{
public:
   /**
    * Add an error to be correlated.
    * @param error Error
    */
   void addError(const Error &error)
   {
      errors_.push(error);
   }

   /**
    * @brief Retrieve the next error to be processed.
    * @return The next error
    */
   [[nodiscard]] Error getError()
   {
      // If there are no more errors, throw an exception.
      if (errors_.empty())
      {
         throw std::out_of_range{"No more errors."};
      }

      // Save the top element.
      Error top{errors_.top()};

      // Remove the top element.
      errors_.pop();

      // Return the saved element.
      return top;
   }

private:
   std::priority_queue<Error> errors_;
};
