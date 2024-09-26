#include "Person.hpp"

#include <utility>
#include <iostream>

namespace HR
{
   Person::Person(const std::string &firstName, const std::string &lastName)
       : Person{firstName, lastName, extractInitials(firstName, lastName)}
   {
   }

   Person::Person() : Person{"", "", ""}
   {
   }

   Person::Person(const Person &src) = default;

   Person &Person::operator=(const Person &rhs) = default;

   inline const std::string &Person::getFirstName() const
   {
      return firstName_;
   }

   void Person::setFirstName(const std::string &firstName)
   {
      firstName_ = firstName;
   }

   inline const std::string &Person::getLastName() const
   {
      return lastName_;
   }

   void Person::setLastName(const std::string &lastName)
   {
      lastName_ = lastName;
   }

   const std::string &Person::getInitials() const
   {
      return initials_;
   }

   void Person::setInitials(const std::string &initials)
   {
      initials_ = initials;
   }

   Person::Person(std::string firstName, std::string lastName, std::string initials)
       : firstName_(std::move(firstName)),
         lastName_(std::move(lastName)),
         initials_(std::move(initials))
   {
   }

   std::string Person::extractInitials(const std::string &firstName, const std::string &lastName)
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

   Person::Person(Person &&src) noexcept
   {
#ifndef NDEBUG
      std::cout << "Move ctor is called for src: " << src << std::endl;
#endif

      swap(src);
   }

   Person &Person::operator=(Person &&rhs) noexcept
   {
#ifndef NDEBUG
      std::cout << "Move assignment is called for lhs: " << *this << std::endl;
#endif

      auto moved{std::move(rhs)};
      swap(moved);

      return *this;
   }

   void Person::swap(Person &other) noexcept
   {
      std::swap(firstName_, other.firstName_);
      std::swap(lastName_, other.lastName_);
      std::swap(initials_, other.initials_);
   }

   Person::~Person() = default;

   std::ostream &operator<<(std::ostream &ostream, const Person &person)
   {
      const char *empty = "EMPTY";
      const auto &firstName = person.getFirstName();
      const auto &lastName = person.getLastName();
      const auto &initials = person.getInitials();
      ostream << "First name: " << (firstName.empty() ? empty : firstName)
              << ", Last name: " << (lastName.empty() ? empty : lastName)
              << ", Initials: " << (initials.empty() ? empty : initials);

      return ostream;
   }

   void swap(Person &first, Person &second)
   {
      first.swap(second);
   }
}

