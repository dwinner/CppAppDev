#include "Person.hpp"
#include <iostream>
#include "Person.Impl.hpp"

namespace hr
{
   Person::Person() : impl_{std::make_unique<Impl>()}
   {
   }

   Person::Person(const std::string& firstName, const std::string& lastName)
      : impl_{std::make_unique<Impl>(firstName, lastName)}
   {
   }

   Person::Person(const std::string& firstName, const std::string& lastName, const std::string& initials)
      : impl_{std::make_unique<Impl>(firstName, lastName, initials)}
   {
   }

   Person::Person(const Person& src)
      : impl_{std::make_unique<Impl>(*src.impl_)}
   {
   }

   Person& Person::operator=(const Person& rhs)
   {
      *impl_ = *rhs.impl_;
      return *this;
   }

   Person::Person(Person&& src) noexcept = default;

   Person& Person::operator=(Person&& rhs) noexcept = default;

   const std::string& Person::getFirstName() const
   {
      return impl_->getFirstName();
   }

   void Person::setFirstName(const std::string& firstName) const
   {
      impl_->setFirstName(firstName);
   }

   const std::string& Person::getLastName() const
   {
      return impl_->getLastName();
   }

   void Person::setLastName(const std::string& lastName) const
   {
      impl_->setLastName(lastName);
   }

   const std::string& Person::getInitials() const
   {
      return impl_->getInitials();
   }

   void Person::setInitials(const std::string& initials) const
   {
      impl_->setInitials(initials);
   }

   Person::~Person() = default;

   bool operator==(const Person& lhs, const Person& rhs)
   {
      return lhs.impl_ == rhs.impl_;
   }

   bool operator!=(const Person& lhs, const Person& rhs)
   {
      return !(lhs == rhs);
   }

   bool operator<(const Person& lhs, const Person& rhs)
   {
      return lhs.impl_ < rhs.impl_;
   }

   bool operator>(const Person& lhs, const Person& rhs)
   {
      return lhs.impl_ > rhs.impl_;
   }

   bool operator<=(const Person& lhs, const Person& rhs)
   {
      return !(rhs > lhs);
   }

   bool operator>=(const Person& lhs, const Person& rhs)
   {
      return !(lhs < rhs);
   }

   std::ostream& operator<<(std::ostream& ostream, const Person& person)
   {
      const auto empty = "EMPTY";
      const auto firstName = person.impl_->getFirstName();
      const auto lastName = person.impl_->getLastName();
      const auto initials = person.impl_->getInitials();
      ostream << "First name: " << (firstName.empty() ? empty : firstName)
         << ", Last name: " << (lastName.empty() ? empty : lastName)
         << ", Initials: " << (initials.empty() ? empty : initials);

      return ostream;
   }
}
