#pragma once

#include <string>
#include <tuple>

#include "Person.hpp"

namespace hr
{
   class Person::Impl
   {
   public:
      Impl(const std::string& firstName, const std::string& lastName);

      Impl(std::string firstName, std::string lastName, std::string initials);

      Impl();

      Impl(const Impl&);

      Impl& operator=(const Impl&);

      Impl(Impl&&) noexcept;

      Impl& operator=(Impl&&) noexcept;

      [[nodiscard]] const std::string& getFirstName() const
      {
         return firstName_;
      }

      void setFirstName(const std::string& firstName)
      {
         firstName_ = firstName;
      }

      [[nodiscard]] const std::string& getLastName() const
      {
         return lastName_;
      }

      void setLastName(const std::string& lastName)
      {
         lastName_ = lastName;
      }

      [[nodiscard]] const std::string& getInitials() const
      {
         return initials_;
      }

      void setInitials(const std::string& initials)
      {
         initials_ = initials;
      }

      static std::string extractInitials(const std::string& firstName, const std::string& lastName);

      ~Impl();

      bool operator==(const Impl& rhs)
      {
         return std::tie(firstName_, lastName_) == std::tie(rhs.firstName_, rhs.lastName_);
      }

      bool operator!=(const Impl& rhs)
      {
         return !(*this == rhs);
      }

      bool operator<(const Impl& rhs)
      {
         return std::tie(firstName_, lastName_) < std::tie(rhs.firstName_, rhs.lastName_);
      }

      bool operator>(const Impl& rhs)
      {
         return *this >= rhs;
      }

      bool operator<=(const Impl& rhs)
      {
         return !(*this > rhs);
      }

      bool operator>=(const Impl& rhs)
      {
         return !(*this < rhs);
      }

   private:
      std::string firstName_;
      std::string lastName_;
      std::string initials_;
   };
}
