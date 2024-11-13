import std;

#include <cstdio>

class File final
{
public:
   explicit File(std::FILE* file) : file_{file}
   {
   }

   ~File()
   {
      reset();
   }

   // Prevent copy construction and copy assignment.
   File(const File& src) = delete;

   File& operator=(const File& rhs) = delete;

   // Allow move construction.
   File(File&& src) noexcept : file_{std::exchange(src.file_, nullptr)}
   {
   }

   // Allow move assignment.
   File& operator=(File&& rhs) noexcept
   {
      if (this != &rhs)
      {
         reset();
         file_ = std::exchange(rhs.file_, nullptr);
      }

      return *this;
   }

   // get(), release(), and reset()
   std::FILE* get() const noexcept
   {
      return file_;
   }

   [[nodiscard]] std::FILE* release() noexcept
   {
      return std::exchange(file_, nullptr);
   }

   void reset(std::FILE* file = nullptr) noexcept
   {
      if (file_)
      {
         std::fclose(file_);
      }

      file_ = file;
   }

private:
   std::FILE* file_{nullptr};
};

int main()
{
   FILE* fileDsc = nullptr;
   errno_t openResult = fopen_s(&fileDsc, "input.txt", "r");
   File myFile{fileDsc};
}
