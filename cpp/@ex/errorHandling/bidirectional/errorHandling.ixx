export module errorHandling;

import <exception>;

export namespace biDir
{
   class FileNotFoundException final : public std::exception
   {
   public:
      [[nodiscard]] FileNotFoundException() = default;

      [[nodiscard]] explicit FileNotFoundException(const char* const message)
         : exception(message)
      {
      }

      [[nodiscard]] FileNotFoundException(const char* const message, const int i)
         : exception(message, i)
      {
      }

      [[nodiscard]] explicit FileNotFoundException(const exception& other)
         : exception(other)
      {
      }
   };
}
