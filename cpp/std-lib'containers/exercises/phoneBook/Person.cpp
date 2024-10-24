#include <format>
#include <ostream>
#include <iomanip>
#include <istream>
#include <sstream>
#include "Person.hpp"

Person::Person(std::string firstName, std::string lastName) :
    firstName_{std::move(firstName)},
    lastName_{std::move(lastName)}
{
   initials_ = std::format("{}{}", firstName_[0], lastName_[0]);
}

Person::Person(std::string firstName, std::string lastName, std::string initials) :
    firstName_{std::move(firstName)},
    lastName_{std::move(lastName)},
    initials_{std::move(initials)}
{
}

void Person::setFirstName(std::string firstName)
{
   firstName_ = std::move(firstName);
}

const std::string &Person::getFirstName() const
{
   return firstName_;
}

const std::string &Person::getLastName() const
{
   return lastName_;
}

void Person::setLastName(std::string lastName)
{
   lastName_ = std::move(lastName);
}

const std::string &Person::getInitials() const
{
   return initials_;
}

void Person::setInitials(std::string initials)
{
   initials_ = std::move(initials);
}

void Person::output(std::ostream &output) const
{
   std::println(output, "{} {} ({})",
                getFirstName(),
                getLastName(),
                getInitials());
}

Person::operator std::string() const
{
   return std::format("{} {}", getFirstName(), getLastName());
}

Person &Person::operator=(const Person &) = default;

Person::Person(Person &&) noexcept = default;

Person &Person::operator=(Person &&) noexcept = default;

Person::~Person() = default;

Person::Person(const Person &) = default;

auto Person::operator<=>(const Person &) const = default;

Person::Person() = default;

std::ostream &operator<<(std::ostream &os, const Person &person)
{
   os << std::quoted(person.getFirstName())
      << std::quoted(person.getLastName())
      << std::quoted(person.getInitials());

   return os;
}

std::istream &operator>>(std::istream &is, Person &person)
{
   std::string firstName, lastName, initials;
   is >> std::quoted(firstName)
      >> std::quoted(lastName)
      >> std::quoted(initials);

   person.setFirstName(std::move(firstName));
   person.setLastName(std::move(lastName));
   person.setInitials(std::move(initials));

   return is;
}

Person operator ""_p(const char *fromStr, std::size_t)
{
   std::istringstream input{fromStr};
   std::string firstName, lastName;
   input >> firstName;
   input >> std::ws;
   getline(input, lastName);

   return Person{std::move(firstName), std::move(lastName)};
}
