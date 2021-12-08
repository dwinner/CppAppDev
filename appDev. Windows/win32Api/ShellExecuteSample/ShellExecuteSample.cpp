/**
 * Installing / managing VS-code extensions from C++
 */

#include "pch.h"
#include "framework.h"
#include "ShellExecuteSample.h"
#include <cassert>
#include "UserEnv.h"
#include <filesystem>
#include <string>
#include <sstream>
#include <regex>
#include <map>

#include "ExtensionEntity.h"

#pragma comment(lib, "userenv.lib")

using namespace std;
namespace fs = std::filesystem;

int main() noexcept
{
   //auto currentExeDir = std::filesystem::current_path();

   HMODULE hModule = ::GetModuleHandle(nullptr);
   if (hModule == nullptr)
   {
      wprintf(L"Fatal Error: GetModuleHandle failed\n");
      return EXIT_FAILURE;
   }

   // initialize MFC and print and error on failure
   if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
   {
      wprintf(L"Fatal Error: MFC initialization failed\n");
      return EXIT_FAILURE;
   }

   fs::path ceVsixPath = findVsix();
   string ceVsixFilename = normalizeVsix(ceVsixPath);
   bool success;
   ExtensionEntity ceExtToInstall = ExtensionEntity::Parse(ceVsixFilename, success);
   assert(success);

   // Find all installed extensions and pack them to entity-set

   // Check extensions have been already installed
   string userDir = getUserHomeDir();
   auto extensionsDir = fs::path(userDir);
   extensionsDir.concat("\\.vscode\\extensions");
   assert(fs::exists(extensionsDir));

   // Get all installed extensions
   map<fs::path, ExtensionEntity> extensionMap;
   for (const auto& directoryEntry : fs::directory_iterator(extensionsDir))
   {
      const auto& path = directoryEntry.path();
      string filename = path.filename().string();
      bool successParse;
      auto entity = ExtensionEntity::Parse(filename, successParse);
      if (successParse)
      {
         extensionMap[path] = entity;
      }
   }

   // Find out if the latest one for caneasy-x.x.x.vsix is installed
   bool installed = false;
   for (auto mapIt = extensionMap.begin(); mapIt != extensionMap.end(); ++mapIt)
   {
      if (mapIt->second == ceExtToInstall)
      {
         installed = true;
         break;
      }
   }

   string codeCmdPath = R"(c:\Users\vinevtsev\AppData\Local\Programs\Microsoft VS Code\bin\code.cmd)";
   assert(fs::exists(codeCmdPath));

   if (!installed)
   {
      auto vsixFileWithExt = ceVsixPath.filename().string();
      installExtension(codeCmdPath, vsixFileWithExt);
   }

   // Find similar and delete all the previous but the latest one
   for (auto mapIt = extensionMap.begin(); mapIt != extensionMap.end(); ++mapIt)
   {
      if (mapIt->second != ceExtToInstall
         && (mapIt->second.GetExtId() == ceExtToInstall.GetExtId()
            && mapIt->second.GetVendor() == ceExtToInstall.GetVendor()))
      {
         remove_all(mapIt->first);
      }
   }

   // If kmasif.capl-vector is installedm than mark it as inactive than
   string caplExtId = "kmasif.capl-vector";
   installExtension(codeCmdPath, caplExtId, false);

   return EXIT_SUCCESS;
}

std::string getUserHomeDir()
{
   TCHAR szHomeDirBuf[MAX_PATH] = {0};
   HANDLE hToken = nullptr;
   VERIFY(OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &hToken ));
   DWORD bufSize = MAX_PATH;
   VERIFY(GetUserProfileDirectory( hToken, szHomeDirBuf, &bufSize ));
   CloseHandle(hToken);
   std::string homeDir = szHomeDirBuf;

   return homeDir;
}

bool installExtension(const std::string& vsCodeCmd, const std::string& extensionPath, const bool install)
{
   constexpr auto operation = "open";
   constexpr auto shell = "cmd";
   const std::string cmdOpt = "/c";
   const std::string vsCodeCommand = install ? "--install-extension" : "--uninstall-extension";
   std::ostringstream fmtStream;
   fmtStream << cmdOpt << " \"" << vsCodeCmd << "\" " << vsCodeCommand << " " << extensionPath;
   const std::string shellLaunchArgs = fmtStream.str();
   const auto cmdParams = shellLaunchArgs.c_str();
   HINSTANCE retVal = ShellExecute(nullptr,
                                   operation,
                                   shell,
                                   cmdParams,
                                   nullptr, // used current execution directory due to shell call issues in Win32 API
                                   SW_HIDE);
   const bool success = retVal > nullptr ? true : false;

   return success;
}

std::vector<fs::path> findFiles(const fs::path& dir, std::function<bool(const fs::path&)> filter)
{
   auto result = std::vector<fs::path>{};

   if (exists(dir))
   {
      for (const auto& entry : fs::recursive_directory_iterator(dir, fs::directory_options::follow_directory_symlink))
      {
         if (is_regular_file(entry) && filter(entry))
         {
            result.push_back(entry);
         }
      }
   }

   return result;
}

fs::path findVsix(const std::string& similarName)
{
   auto ext = ".vsix";

   // Find file *caneasy*.vsix in the current directory;
   const auto vsixList = findFiles(fs::current_path(),
                                   [similarName, ext](const fs::path& path)
                                   {
                                      auto fileName = path.string();
                                      return fileName.find(similarName) != std::string::npos
                                         && path.has_extension()
                                         && path.extension() == ext;
                                   });

   // There should be only one vsix in the current directory
   assert(vsixList.size() == 1);
   fs::path vsixPath = vsixList[0];

   return vsixPath;
}

std::string normalizeVsix(const fs::path& vsixPath, const std::string& vendorName)
{
   // Adapt the name extId-x.x.x.vsix to vendor.extId-x.x.x
   std::string vsixFilename(vendorName + ".");
   auto vsixFileWithExt = vsixPath.filename().string();
   size_t lastIdx = vsixFileWithExt.find_last_of('.');
   std::string rawVsixName = vsixFileWithExt.substr(0, lastIdx);
   vsixFilename.append(rawVsixName);

   return vsixFilename;
}
