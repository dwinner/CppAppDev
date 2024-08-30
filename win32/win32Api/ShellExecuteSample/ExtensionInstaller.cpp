#include "pch.h"
#include "ExtensionInstaller.h"
#include <UserEnv.h>
#include <sstream>
#include "InstallationError.h"

#pragma comment(lib, "userenv.lib")

namespace vscode
{
   namespace fs = std::filesystem;
   using namespace std;

   void ExtensionInstaller::Apply()
   {
      const fs::path ceVsixPath = FindVsix();
      const string ceVsixFilename = NormalizeVsix(ceVsixPath);
      bool success;
      const ExtensionEntity ceExtToInstall = ExtensionEntity::Parse(ceVsixFilename, success);
      if (!success)
      {
         throw InstallationError("Bad formatting file name: " + ceVsixFilename);
      }

      const map<fs::path, ExtensionEntity> extensionMap = GetInstalledExtensions();
      if (const bool installed = IsExtensionInstalled(ceExtToInstall, extensionMap); !installed)
      {
         const auto vsixFileWithExt = ceVsixPath.filename().string();
         InstallExtension(codeCmd_, vsixFileWithExt);
      }

      RemoveSimilar(ceExtToInstall, extensionMap);

      // If kmasif.capl-vector is installed, then mark it as inactive than
      const string caplExtId = "kmasif.capl-vector";
      InstallExtension(codeCmd_, caplExtId, false);
   }

   std::string ExtensionInstaller::GetUserHomeDir()
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

   bool ExtensionInstaller::InstallExtension(const string& vsCodeCmd, const string& extensionPath,
                                             const bool install)
   {
      constexpr auto operation = "open";
      constexpr auto shell = "cmd";
      const string cmdOpt = "/c";
      const string vsCodeCommand = install ? "--install-extension" : "--uninstall-extension";
      ostringstream fmtStream;
      fmtStream << cmdOpt << " \"" << vsCodeCmd << "\" " << vsCodeCommand << " " << extensionPath;
      const string shellLaunchArgs = fmtStream.str();
      const auto cmdParams = shellLaunchArgs.c_str();
      HINSTANCE retVal = ShellExecute(nullptr,
                                      operation,
                                      shell,
                                      cmdParams,
                                      // used current execution directory due to shell call issues in Win32 API
                                      nullptr,
                                      SW_HIDE);
      const bool success = retVal > nullptr ? true : false;

      return success;
   }

   vector<fs::path> ExtensionInstaller::FindFiles(const fs::path& dir, const function<bool(const fs::path&)>& filter)
   {
      auto result = vector<fs::path>{};

      if (exists(dir))
      {
         for (const auto& entry :
              fs::recursive_directory_iterator(dir, fs::directory_options::follow_directory_symlink))
         {
            if (is_regular_file(entry) && filter(entry))
            {
               result.push_back(entry);
            }
         }
      }

      return result;
   }

   map<fs::path, ExtensionEntity> ExtensionInstaller::GetInstalledExtensions()
   {
      map<fs::path, ExtensionEntity> extensionMap;

      // Check extensions have been already installed
      const string userDir = GetUserHomeDir();
      auto extensionsDir = fs::path(userDir);
      extensionsDir.concat("\\.vscode\\extensions");
      if (!exists(extensionsDir))
      {
         throw InstallationError("Extension folder doesn't exist: " + extensionsDir.filename().string());
      }

      // Get all installed extensions
      for (const auto& directoryEntry : fs::directory_iterator(extensionsDir))
      {
         const auto& path = directoryEntry.path();
         string filename = path.filename().string();
         bool successParse;
         const auto entity = ExtensionEntity::Parse(filename, successParse);
         if (successParse)
         {
            extensionMap[path] = entity;
         }
      }

      return extensionMap;
   }

   bool ExtensionInstaller::IsExtensionInstalled(const ExtensionEntity& extensionEntity,
                                                 const map<fs::path, ExtensionEntity>& extensionMap)
   {
      bool installed = false;
      for (auto mapIt = extensionMap.begin(); mapIt != extensionMap.end(); ++mapIt)
      {
         if (mapIt->second == extensionEntity)
         {
            installed = true;
            break;
         }
      }

      return installed;
   }

   void ExtensionInstaller::RemoveSimilar(const ExtensionEntity& extensionEntity,
                                          const map<fs::path, ExtensionEntity>& extensionMap)
   {
      for (auto mapIt = extensionMap.begin(); mapIt != extensionMap.end(); ++mapIt)
      {
         if (mapIt->second != extensionEntity
            && (mapIt->second.GetExtId() == extensionEntity.GetExtId()
               && mapIt->second.GetVendor() == extensionEntity.GetVendor()))
         {
            remove_all(mapIt->first);
         }
      }
   }

   fs::path ExtensionInstaller::FindVsix()
   {
      fs::path ext(".vsix");

      // Find file *caneasy*.vsix in the current directory;
      const auto vsixList = FindFiles(fs::current_path(),
                                      [ext, this](const fs::path& path)
                                      {
                                         auto fileName = path.string();
                                         return fileName.find(extensionId_) != std::string::npos
                                            && path.has_extension()
                                            && path.extension() == ext;
                                      });

      // There should be only one vsix in the current directory
      if (vsixList.size() != 1)
      {
         throw InstallationError("Vsix file with extension " + extensionId_ + " isn't found");
      }

      fs::path vsixPath = vsixList[0];

      return vsixPath;
   }

   string ExtensionInstaller::NormalizeVsix(const fs::path& vsixPath) const
   {
      // Adapt the name extId-x.x.x.vsix to vendor.extId-x.x.x
      std::string vsixFilename(vendorName_ + ".");
      const auto vsixFileWithExt = vsixPath.filename().string();
      const size_t lastIdx = vsixFileWithExt.find_last_of('.');
      const std::string rawVsixName = vsixFileWithExt.substr(0, lastIdx);
      vsixFilename.append(rawVsixName);

      return vsixFilename;
   }
}
