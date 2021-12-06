#include "pch.h"
#include "ExtensionEntity.h"

#include <utility>

ExtensionEntity ExtensionEntity::Parse(std::string extensionPattern)
{
   ExtensionEntity entity;
   return entity;
}

ExtensionEntity::ExtensionEntity() = default;

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
