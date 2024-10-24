#pragma once

#include <stdexcept>
#include <string_view>

class NoSuchPerson : std::exception
{
public:
   ~NoSuchPerson() noexcept override = default;

   explicit NoSuchPerson(std::string_view errorMsg)
       : message_(errorMsg)
   {
   }

   [[nodiscard]] const char *what() const override
   {
      return message_.c_str();
   }

private:
   std::string message_;
};
