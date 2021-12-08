#pragma once
#include <filesystem>
#include <functional>
#include <map>
#include <utility>
#include <vector>
#include "ExtensionEntity.h"

namespace vscode
{
   class ExtensionInstaller
   {
   public:
      void Apply();

      [[nodiscard]] ExtensionInstaller(std::string vendorName, std::string extensionId, std::string codeCmd)
         : vendorName_(std::move(vendorName)),
           extensionId_(std::move(extensionId)),
           codeCmd_(std::move(codeCmd))
      {
      }

   private:
      std::string vendorName_;
      std::string extensionId_;
      std::string codeCmd_;

      static std::string GetUserHomeDir();

      static inline bool InstallExtension(const std::string& vsCodeCmd, const std::string& extensionPath,
                                          bool install = true);

      static std::vector<std::filesystem::path> FindFiles(const std::filesystem::path& dir,
                                                          const std::function<bool(const std::filesystem::path&)>
                                                          & filter);

      static std::map<std::filesystem::path, ExtensionEntity> GetInstalledExtensions();

      static bool IsExtensionInstalled(const ExtensionEntity& extensionEntity,
                                       const std::map<std::filesystem::path, ExtensionEntity>& extensionMap);

      static void RemoveSimilar(const ExtensionEntity& extensionEntity,
                                const std::map<std::filesystem::path, ExtensionEntity>& extensionMap);

      std::filesystem::path FindVsix();

      inline std::string NormalizeVsix(const std::filesystem::path& vsixPath) const;
   };
}
