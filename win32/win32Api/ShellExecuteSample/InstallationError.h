#pragma once

namespace vscode
{
   class InstallationError final : std::exception
   {
   public:
      [[nodiscard]] explicit InstallationError(std::string message);

      [[nodiscard]] inline const char* what() const override;

   private:
      std::string message_;
   };
}
