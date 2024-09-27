#include "Person.hpp"

#include <utility>
#include <iostream>

namespace HR
{
   using namespace std;

   Person::Person(const string &firstName, const string &lastName)
       : Person{firstName, lastName, extractInitials(firstName, lastName)}
   {
   }

   Person::Person() : Person{"", "", ""}
   {
   }

   Person::Person(const Person &src) = default;

   Person &Person::operator=(const Person &rhs) = default;

   inline const string &Person::getFirstName() const
   {
      return firstName_;
   }

   void Person::setFirstName(const string &firstName)
   {
      firstName_ = firstName;
   }

   inline const string &Person::getLastName() const
   {
      return lastName_;
   }

   void Person::setLastName(const string &lastName)
   {
      lastName_ = lastName;
   }

   const string &Person::getInitials() const
   {
      return initials_;
   }

   void Person::setInitials(const string &initials)
   {
      initials_ = initials;
   }

   Person::Person(string firstName, string lastName, string initials)
       : firstName_(std::move(firstName)),
         lastName_(std::move(lastName)),
         initials_(std::move(initials))
   {
   }

   string Person::extractInitials(const string &firstName, const string &lastName)
   {
      string initials;
      if (!firstName.empty())
      {
         initials += static_cast<char>(toupper(firstName[0]));
      }

      if (!lastName.empty())
      {
         initials += static_cast<char>(toupper(lastName[0]));
      }

      return initials;
   }

   Person::Person(Person &&src) noexcept
   {
      swap(src);
   }

   Person &Person::operator=(Person &&rhs) noexcept
   {
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

   void swap(Person &first, Person &second) noexcept
   {
      first.swap(second);
   }

   bool Person::operator==(const Person &rhs) const
   {
      return std::tie(firstName_, lastName_, initials_)
             == std::tie(rhs.firstName_, rhs.lastName_, rhs.initials_);
   }

   std::partial_ordering Person::operator<=>(const Person &rhs)
   {
      return std::tie(firstName_, lastName_, initials_)
             <=> std::tie(rhs.firstName_, rhs.lastName_, rhs.initials_);
   }

   Person::~Person() = default;
}
