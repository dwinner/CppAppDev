#include "Person.Impl.hpp"

#include <utility>
#include <iostream>

#include "Person.hpp"

namespace hr
{
   Person::Impl::Impl(const std::string& firstName, const std::string& lastName)
      : Impl{firstName, lastName, extractInitials(firstName, lastName)}
   {
   }

   Person::Impl::Impl(std::string firstName, std::string lastName, std::string initials)
      : firstName_(std::move(firstName)),
        lastName_(std::move(lastName)),
        initials_(std::move(initials))
   {
   }

   Person::Impl::Impl(): Impl{"", "", ""}
   {
   }

   Person::Impl::Impl(const Impl&) = default;

   Person::Impl& Person::Impl::operator=(const Impl&) = default;

   Person::Impl::Impl(Impl&&) noexcept = default;

   Person::Impl& Person::Impl::operator=(Impl&&) noexcept = default;

   std::string Person::Impl::extractInitials(const std::string& firstName, const std::string& lastName)
   {
      std::string initials;
      if (!firstName.empty())
      {
         initials += static_cast<char>(std::toupper(firstName[0]));
      }

      if (!lastName.empty())
      {
         initials += static_cast<char>(std::toupper(lastName[0]));
      }

      return initials;
   }

   Person::Impl::~Impl() = default;
}
