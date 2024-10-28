#pragma once

#include "Error.hpp"
#include <stack>

/**
 * @brief Simple ErrorCorrelator class that returns highest priority errors first.
 */
class ErrorCorrelator final
{
public:
   // Add an error to be correlated.
   void addError(const Error &error)
   {
      errors_.push(error);
   }

   // Retrieve the next error to be processed.
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
   std::stack<Error> errors_;
};
