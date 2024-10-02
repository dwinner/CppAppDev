#include "Person.hpp"

#include <utility>
#include <sstream>
#include <format>

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

   inline const string &Person::getLastName() const
   {
      return lastName_;
   }

   const string &Person::getInitials() const
   {
      return initials_;
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

   Person::Person(Person &&src) noexcept = default;

   Person &Person::operator=(Person &&rhs) noexcept = default;

   std::ostream &operator<<(std::ostream &ostream, const Person &person)
   {
      std::string clsName = person.getClsName();
      std::string objInfo = person.toString();
      ostream << std::format("{}: {}", clsName, objInfo);

      return ostream;
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

   std::string Person::toString() const
   {
      std::ostringstream strStream;

      const char *empty = "EMPTY";
      const auto &firstName = getFirstName();
      const auto &lastName = getLastName();
      const auto &initials = getInitials();
      strStream << "First name: " << (firstName.empty() ? empty : firstName)
                << ", Last name: " << (lastName.empty() ? empty : lastName)
                << ", Initials: " << (initials.empty() ? empty : initials);

      return strStream.str();
   }

   std::string Person::getClsName() const
   {
      return "Person";
   }

   Person::~Person() = default;
}
