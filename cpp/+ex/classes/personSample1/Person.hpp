#ifndef PERSONSAMPLE_PERSON_HPP
#define PERSONSAMPLE_PERSON_HPP

#include <string>
#include <ostream>

class Person
{
public:
   Person();

   explicit Person(const std::string &firstName, const std::string &lastName);

   explicit Person(std::string firstName, std::string lastName, std::string initials);

   Person(const Person &src);

   Person &operator=(const Person &rhs);

   [[nodiscard]] inline const std::string &getFirstName() const;

   void setFirstName(const std::string &firstName);

   [[nodiscard]] inline const std::string &getLastName() const;

   void setLastName(const std::string &lastName);

   [[nodiscard]] inline const std::string &getInitials() const;

   void setInitials(const std::string &initials);

   virtual ~Person();

private:
   [[nodiscard]] static std::string extractInitials(const std::string &firstName, const std::string &lastName);

   std::string firstName_;
   std::string lastName_;
   std::string initials_;
};


std::ostream &operator<<(std::ostream &ostream, const Person &person);

#endif //PERSONSAMPLE_PERSON_HPP
