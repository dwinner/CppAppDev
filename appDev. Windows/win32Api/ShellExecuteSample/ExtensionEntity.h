#pragma once
#include <ostream>
#include <utility>

class ExtensionEntity
{
public:
   static ExtensionEntity Parse(std::string extensionPattern);

   [[nodiscard]] ExtensionEntity(int major, int minor, int patch,
                                 std::string vendor,
                                 std::string id);

   ExtensionEntity(const ExtensionEntity& other);
   
   ExtensionEntity(ExtensionEntity&& other) noexcept;

   ExtensionEntity& operator=(ExtensionEntity other);

   [[nodiscard]] int GetMajor() const;

   [[nodiscard]] int GetMinor() const;

   [[nodiscard]] int GetPatch() const;

   [[nodiscard]] std::string GetVendor() const;

   [[nodiscard]] std::string GetId() const;

   friend std::ostream& operator<<(std::ostream& os, const ExtensionEntity& obj);

   friend bool operator==(const ExtensionEntity& lhs, const ExtensionEntity& rhs);

   friend bool operator!=(const ExtensionEntity& lhs, const ExtensionEntity& rhs);

   friend bool operator<(const ExtensionEntity& lhs, const ExtensionEntity& rhs);

   friend bool operator<=(const ExtensionEntity& lhs, const ExtensionEntity& rhs);

   friend bool operator>(const ExtensionEntity& lhs, const ExtensionEntity& rhs);

   friend bool operator>=(const ExtensionEntity& lhs, const ExtensionEntity& rhs);

private:
   int major_;
   int minor_;
   int patch_;
   std::string vendor_;
   std::string id_;
};
