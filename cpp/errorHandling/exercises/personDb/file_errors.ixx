export module file_errors;

import std;
import <exception>;

export namespace fileErrors
{
   class FileErrorBase : public std::exception
   {
   public:
      explicit FileErrorBase(std::string filename)
         : filename_{std::move(filename)}
      {
      }

      const char* what() const noexcept override
      {
         return message_.c_str();
      }

      virtual const std::string& getFilename() const noexcept
      {
         return filename_;
      }

   protected:
      virtual void setMessage(std::string message)
      {
         message_ = std::move(message);
      }

   private:
      std::string filename_;
      std::string message_;
   };


   class FileOpenError : public FileErrorBase
   {
   public:
      explicit FileOpenError(std::string filename)
         : FileErrorBase{std::move(filename)}
      {
         FileErrorBase::setMessage(
            std::format("Unable to open {}.", FileErrorBase::getFilename()));
      }
   };


   class FileReadError : public FileErrorBase
   {
   public:
      explicit FileReadError(std::string filename, size_t lineNumber) :
         FileErrorBase{std::move(filename)},
         lineNumber_{lineNumber}
      {
         FileErrorBase::setMessage(std::format("Error reading {}, line {}.",
                                               FileErrorBase::getFilename(),
                                               lineNumber));
      }

      virtual size_t getLineNumber() const noexcept
      {
         return lineNumber_;
      }

   private:
      size_t lineNumber_{0};
   };
}
