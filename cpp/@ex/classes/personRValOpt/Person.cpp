#include "Person.hpp"

#include <utility>

Person::Person(const std::string& firstName, const std::string& lastName)
   : Person{firstName, lastName, extractInitials(firstName, lastName)}
{
}

Person::Person() : Person{"", "", ""}
{
}

Person::Person(const Person&) = default;

Person& Person::operator=(const Person&) = default;

Person::Person(Person&&) noexcept = default;

Person& Person::operator=(Person&&) noexcept = default;

Person::Person(std::string firstName, std::string lastName, std::string initials)
   : firstName_(std::move(firstName)),
     lastName_(std::move(lastName)),
     initials_(std::move(initials))
{
}

std::string Person::extractInitials(const std::string& firstName, const std::string& lastName)
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

Person::~Person() = default;

std::ostream& operator<<(std::ostream& ostream, const Person& person)
{
   ostream <<
      "First name: " << person.getFirstName() <<
      ", Last name: " << person.getLastName() <<
      ", Initials: " << person.getInitials();
   return ostream;
}
