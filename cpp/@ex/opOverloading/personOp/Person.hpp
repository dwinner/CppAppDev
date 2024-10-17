#ifndef PERSONOP_PERSON_HPP
#define PERSONOP_PERSON_HPP

#include <string>

class Person
{
public:
   explicit Person(std::string firstName, std::string lastName);

   Person();

   explicit Person(std::string firstName, std::string lastName, std::string initials);

   inline const std::string &getFirstName() const;

   inline void setFirstName(std::string firstName);

   inline const std::string &getLastName() const;

   inline void setLastName(std::string lastName);

   inline const std::string &getInitials() const;

   inline void setInitials(std::string initials);

   [[nodiscard]] auto operator<=>(const Person &) const;

   void output(std::ostream &output) const;

   operator std::string() const;

   friend Person operator ""_p(const char *fullName, std::size_t size);

private:
   std::string m_firstName;
   std::string m_lastName;
   std::string m_initials;
};

std::ostream &operator<<(std::ostream &ostream, const Person &person);

std::istream &operator>>(std::istream &istream, Person &person);

#endif //PERSONOP_PERSON_HPP
