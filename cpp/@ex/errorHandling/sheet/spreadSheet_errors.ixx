export module spreadSheet_errors;

import std;
import <exception>;

export namespace spreadSheet
{
   class OutOfMemoryException final : public std::exception
   {
   public:
      explicit OutOfMemoryException(std::string message)
         : message_{std::move(message)}
      {
      }

      const char* what() const noexcept override
      {
         return message_.c_str();
      }

   private:
      std::string message_;
   };

   class InvalidCoordinateException final : public std::exception
   {
   public:
      [[nodiscard]] InvalidCoordinateException(
         const std::size_t invalidCoord,
         const std::string& message)
         : invalidCoord_(invalidCoord),
           errorMessage_(message)
      {
      }

      [[nodiscard]] InvalidCoordinateException(
         const char* const aMessage,
         const std::size_t invalidCoord,
         const std::string& message)
         : exception(aMessage),
           invalidCoord_(invalidCoord),
           errorMessage_(message)
      {
      }

      [[nodiscard]] InvalidCoordinateException(
         const char* const aMessage,
         const int i,
         const std::size_t invalidCoord,
         const std::string& message)
         : exception(aMessage, i),
           invalidCoord_(invalidCoord),
           errorMessage_(message)
      {
      }

      [[nodiscard]] InvalidCoordinateException(
         const exception& anError,
         const std::size_t invalidCoord,
         const std::string& message)
         : exception(anError),
           invalidCoord_(invalidCoord),
           errorMessage_(message)
      {
      }

      [[nodiscard]] const char* what() const override
      {
         return errorMessage_.c_str();
      }

   private:
      std::size_t invalidCoord_;
      std::string errorMessage_;
   };
}
