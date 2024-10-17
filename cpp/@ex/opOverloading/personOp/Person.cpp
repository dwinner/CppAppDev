#include <format>
#include <sstream>
#include <vector>
#include "Person.hpp"

auto Person::operator<=>(const Person &) const = default;

void Person::setInitials(std::string initials)
{
   m_initials = std::move(initials);
}

const std::string &Person::getInitials() const
{
   return m_initials;
}

void Person::setLastName(std::string lastName)
{
   m_lastName = std::move(lastName);
}

const std::string &Person::getLastName() const
{
   return m_lastName;
}

void Person::setFirstName(std::string firstName)
{
   m_firstName = std::move(firstName);
}

const std::string &Person::getFirstName() const
{
   return m_firstName;
}

Person::Person(std::string firstName, std::string lastName, std::string initials) :
    m_firstName{std::move(firstName)}, m_lastName{std::move(lastName)}, m_initials{std::move(initials)}
{

}

Person::Person(std::string firstName, std::string lastName) :
    m_firstName{std::move(firstName)}, m_lastName{std::move(lastName)}
{
   m_initials = std::format("{}{}", m_firstName[0], m_lastName[0]);
}

void Person::output(std::ostream &output) const
{
   std::string outPerson = std::format("{} {} ({})", getFirstName(), getLastName(), getInitials());
   output << outPerson;
}

Person::operator std::string() const
{
   std::string fullName = std::format("{} {}", getFirstName(), getLastName());
   return fullName;
}

Person operator ""_p(const char *fullName, std::size_t size)
{
   std::stringstream strStream{fullName};
   std::string word;
   vector <std::string> words;
   while (strStream >> word)
   {
      words.push_back(word);
   }

   const auto wordsSize = words.size();
   if (wordsSize <= 0)
   {
      return Person{"", ""};
   }
   else if (wordsSize == 1)
   {
      return Person{words[0], ""};
   }
   else
   {
      return Person{words[0], words[1]};
   }
}

Person::Person() = default;

std::ostream &operator<<(std::ostream &ostream, const Person &person)
{
   person.output(ostream);
   return ostream;
}

std::istream &operator>>(std::istream &istream, Person &person)
{
   std::string fName;
   std::string lName;
   istream >> fName;
   istream >> lName;
   person.setFirstName(fName);
   person.setLastName(lName);

   return istream;
}
