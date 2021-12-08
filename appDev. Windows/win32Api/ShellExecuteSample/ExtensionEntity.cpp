#include "pch.h"
#include "ExtensionEntity.h"
#include <regex>
#include <string>
#include <utility>

ExtensionEntity ExtensionEntity::Parse(const std::string& vsixFilename, bool& success)
{
   // Pack vendor.extId-x.x.x to entity via parsing RegEx-object
   const std::regex extRe{R"(^([\w]+)\.([\w]+)\-([\d]+)\.([\d])\.([\d])$)"};
   std::smatch extMatch;

   // Skip extId with greedy '-' matches there (like extId=tsl-problem-matcher)
   if (bool matchFound = std::regex_match(vsixFilename, extMatch, extRe); !matchFound)
   {
      ExtensionEntity dummyEntity;
      success = false;
      return dummyEntity;
   }

   // Wrap RegEx-matches into pdo entity
   std::string vendor = extMatch[1];
   std::string extId = extMatch[2];
   int majorVersion = std::stoi(extMatch[3]);
   int minorVersion = std::stoi(extMatch[4]);
   int patchVersion = std::stoi(extMatch[5]);
   ExtensionEntity targetEntity(majorVersion, minorVersion, patchVersion, vendor, extId);
   success = true;

   return targetEntity;
}

ExtensionEntity::ExtensionEntity()
   : ExtensionEntity(0, 0, 0, "", "")
{
}

ExtensionEntity::ExtensionEntity(const int major, const int minor, const int patch,
                                 std::string vendor,
                                 std::string extId)
   : major_(major),
     minor_(minor),
     patch_(patch),
     vendor_(std::move(vendor)),
     extId_(std::move(extId))
{
}

int ExtensionEntity::GetMajor() const
{
   return major_;
}

int ExtensionEntity::GetMinor() const
{
   return minor_;
}

int ExtensionEntity::GetPatch() const
{
   return patch_;
}

std::string ExtensionEntity::GetVendor() const
{
   return vendor_;
}

std::string ExtensionEntity::GetExtId() const
{
   return extId_;
}
