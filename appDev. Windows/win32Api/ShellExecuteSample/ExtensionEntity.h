#pragma once
#include <ostream>

class ExtensionEntity
{
public:
   static ExtensionEntity Parse(std::string extensionPattern);

   ExtensionEntity();

   [[nodiscard]] ExtensionEntity(int major, int minor, int patch,
                                 std::string vendor,
                                 std::string id);

   [[nodiscard]] int GetMajor() const;

   [[nodiscard]] int GetMinor() const;

   [[nodiscard]] int GetPatch() const;

   [[nodiscard]] std::string GetVendor() const;

   [[nodiscard]] std::string GetId() const;

private:
   int major_;
   int minor_;
   int patch_;
   std::string vendor_;
   std::string id_;
};
