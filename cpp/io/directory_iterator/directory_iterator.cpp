import std;

using namespace std;
using namespace std::filesystem;

void PrintDirectoryStructure(const path& aPath, const unsigned aLevel = 0)
{
   if (!exists(aPath))
   {
      return;
   }

   const string spacer(aLevel * 2, ' ');

   if (is_regular_file(aPath))
   {
      println("{}File: {} ({} bytes)", spacer, aPath.string(), file_size(aPath));
   }
   else if (is_directory(aPath))
   {
      println("{}Dir: {}", spacer, aPath.string());
      for (auto& entry : directory_iterator{aPath})
      {
         PrintDirectoryStructure(entry, aLevel + 1);
      }
   }
}

int main()
{
   path p{R"(c:\Windows)"};
   PrintDirectoryStructure(p);
}
