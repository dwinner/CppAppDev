import std;

using namespace std;
using namespace std::filesystem;

void PrintDirectoryStructure(const path& aPath)
{
   if (!exists(aPath))
   {
      return;
   }

   const recursive_directory_iterator begin{aPath};
   const recursive_directory_iterator end{};
   for (auto iter{begin}; iter != end; ++iter)
   {
      const string spacer(iter.depth() * 2, ' ');
      if (auto& entry{*iter}; is_regular_file(entry))
      {
         println("{}File: {} ({} bytes)", spacer, entry.path().string(), file_size(entry));
      }
      else if (is_directory(entry))
      {
         println("{}Dir: {}", spacer, entry.path().string());
      }
   }
}

int main()
{
   const path winDir{R"(c:\Windows)"};
   PrintDirectoryStructure(winDir);
}
