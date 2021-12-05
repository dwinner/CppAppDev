#include "pch.h"
#include "ExtensionEntity.h"

ExtensionEntity ExtensionEntity::Parse(std::string extensionPattern)
{
}

ExtensionEntity::ExtensionEntity(const int major, const int minor, const int patch, std::string vendor, std::string id)
   : major_(major),
     minor_(minor),
     patch_(patch),
     vendor_(std::move(vendor)),
     id_(std::move(id))
{
}

ExtensionEntity::ExtensionEntity(const ExtensionEntity& other)
   : major_{other.major_},
     minor_{other.minor_},
     patch_{other.patch_},
     vendor_{other.vendor_},
     id_{other.id_}
{
}

ExtensionEntity::ExtensionEntity(ExtensionEntity&& other) noexcept
   : major_{other.major_},
     minor_{other.minor_},
     patch_{other.patch_},
     vendor_{std::move(other.vendor_)},
     id_{std::move(other.id_)}
{
}

ExtensionEntity& ExtensionEntity::operator=(ExtensionEntity other)
{
   using std::swap;
   swap(*this, other);
   return *this;
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

std::ostream& operator<<(std::ostream& os, const ExtensionEntity& obj)
{
   return os
      << "Major: " << obj.major_
      << " Minor: " << obj.minor_
      << " Patch: " << obj.patch_
      << " Vendor: " << obj.vendor_.c_str()
      << " Id: " << obj.id_.c_str();
}

bool operator==(const ExtensionEntity& lhs, const ExtensionEntity& rhs)
{
   return
      lhs.major_ == rhs.major_
      && lhs.minor_ == rhs.minor_
      && lhs.patch_ == rhs.patch_
      && lhs.vendor_ == rhs.vendor_
      && lhs.id_ == rhs.id_;
}

bool operator!=(const ExtensionEntity& lhs, const ExtensionEntity& rhs)
{
   return !(lhs == rhs);
}

bool operator<(const ExtensionEntity& lhs, const ExtensionEntity& rhs)
{
   if (lhs.major_ < rhs.major_)
      return true;
   if (rhs.major_ < lhs.major_)
      return false;
   if (lhs.minor_ < rhs.minor_)
      return true;
   if (rhs.minor_ < lhs.minor_)
      return false;
   if (lhs.patch_ < rhs.patch_)
      return true;
   if (rhs.patch_ < lhs.patch_)
      return false;
   if (lhs.vendor_ < rhs.vendor_)
      return true;
   if (rhs.vendor_ < lhs.vendor_)
      return false;
   return lhs.id_ < rhs.id_;
}

bool operator<=(const ExtensionEntity& lhs, const ExtensionEntity& rhs)
{
   return !(rhs < lhs);
}

bool operator>(const ExtensionEntity& lhs, const ExtensionEntity& rhs)
{
   return rhs < lhs;
}

bool operator>=(const ExtensionEntity& lhs, const ExtensionEntity& rhs)
{
   return !(lhs < rhs);
}
