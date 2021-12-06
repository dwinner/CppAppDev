#include "pch.h"
#include "ExtensionEntity.h"

ExtensionEntity ExtensionEntity::Parse(std::string extensionPattern)
{
   ExtensionEntity entity;
   return entity;
}

ExtensionEntity::ExtensionEntity() = default;

ExtensionEntity::ExtensionEntity(const int major, const int minor, const int patch, std::string vendor, std::string id)
   : major_(major),
     minor_(minor),
     patch_(patch),
     vendor_(std::move(vendor)),
     id_(std::move(id))
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

std::string ExtensionEntity::GetId() const
{
   return id_;
}
