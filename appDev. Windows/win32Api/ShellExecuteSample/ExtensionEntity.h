#pragma once
#include <ostream>

class ExtensionEntity
{
public:
   static ExtensionEntity Parse(const std::string& vsixFilename, bool& success);

   ExtensionEntity();

   [[nodiscard]] ExtensionEntity(int major, int minor, int patch,
                                 std::string vendor,
                                 std::string extId);

   [[nodiscard]] int GetMajor() const;

   [[nodiscard]] int GetMinor() const;

   [[nodiscard]] int GetPatch() const;

   [[nodiscard]] std::string GetVendor() const;

   [[nodiscard]] std::string GetExtId() const;

   friend bool operator==(const ExtensionEntity& lhs, const ExtensionEntity& rhs)
   {
      return
         lhs.major_ == rhs.major_
         && lhs.minor_ == rhs.minor_
         && lhs.patch_ == rhs.patch_
         && lhs.vendor_ == rhs.vendor_
         && lhs.extId_ == rhs.extId_;
   }

   friend bool operator!=(const ExtensionEntity& lhs, const ExtensionEntity& rhs)
   {
      return !(lhs == rhs);
   }

private:
   int major_;
   int minor_;
   int patch_;
   std::string vendor_;
   std::string extId_;
};
