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
#include <set>
#include <sstream>
#include <regex>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <iomanip>

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

   // Find file *caneasy*.vsix in the current directory;
   const auto vsixList = findFiles(fs::current_path(), [](const fs::path& path)
   {
      auto fileName = path.string();
      return fileName.find("caneasy") != std::string::npos
         && path.has_extension()
         && path.extension() == ".vsix";
   });

   // There should be only one vsix in the current directory
   assert(vsixList.size() == 1);
   fs::path vsixPath = vsixList[0];

   // Adapt the name caneasy-x.x.x.vsix to schleisheimer.caneasy-x.x.x
   string vsixFilename("schleisheimer.");
   auto vsixFileWithExt = vsixPath.filename().string();
   size_t lastIdx = vsixFileWithExt.find_last_of('.');
   string rawVsixName = vsixFileWithExt.substr(0, lastIdx);
   vsixFilename.append(rawVsixName);

   // Pack schleisheimer.caneasy-x.x.x to entity via parsing RegEx-object
   const regex extRe{R"(^([\w]+)\.([\w]+)\-([\d])\.([\d])\.([\d])$)"};
   std::smatch extMatch;
   bool matchFound = regex_match(vsixFilename, extMatch, extRe);
   assert(matchFound);

   // Wrap RegEx-matches into pdo entity
   string vendor = extMatch[1];
   string extId = extMatch[2];
   int majorVersion = std::stoi(extMatch[3]);
   int minorVersion = std::stoi(extMatch[4]);
   int patchVersion = std::stoi(extMatch[5]);
   ExtensionEntity targetEntity(majorVersion, minorVersion, patchVersion, vendor, extId);

   // TODO: Find all installed extensions and pack them to entity-set

   // Check extensions have been already installed
   string userDir = getUserHomeDir();
   auto extensionsDir = fs::path(userDir);
   extensionsDir.concat("\\.vscode\\extensions");
   assert(fs::exists(extensionsDir));

   // Get all installed extensions
   set<fs::path> extensionSet;
   for (const auto& directoryEntry : fs::directory_iterator(extensionsDir))
   {
      extensionSet.insert(directoryEntry.path());
   }
   
   abort();
   // TODO: 5.    Find out if the latest one for caneasy-x.x.x.vsix is installed;
   // TODO: 6.    If the latest one is there - go to item 7;
   // TODO: 7.    Find similar extensions for caneasy have been installed already;
   // TODO: 8.    If similar extensions are more than one - delete all but latest;
   // TODO: 9.    If the latest one isn't there - install it then and go to item 7;
   // TODO: 10.   Find if kmasif.capl-vector is installed;
   // TODO: 11.   If kmasif.capl-vector is installed - delete it psysically

   string caplExtId = "kmasif.capl-vector";

   // split path to extension name, major.minor.patch version
   fs::path ceVsixPath(vsixFileWithExt);

   string codeCmdPath = R"(c:\Users\vinevtsev\AppData\Local\Programs\Microsoft VS Code\bin\code.cmd)";
   assert(fs::exists(codeCmdPath));
   installExtension(codeCmdPath, vsixFileWithExt);
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
