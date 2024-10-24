#pragma once

#include <string>

class Person
{
public:
   explicit Person(std::string firstName, std::string lastName);

   Person();

   ~Person();

   Person(const Person &);

   Person(Person &&) noexcept;

   Person &operator=(const Person &);

   Person &operator=(Person &&) noexcept;

   bool operator==(const Person &rhs) const
   {
      return std::tie(firstName_, lastName_) == std::tie(rhs.firstName_, rhs.lastName_);
   }

   bool operator!=(const Person &rhs) const
   {
      return !(rhs == *this);
   }

   explicit Person(std::string firstName, std::string lastName, std::string initials);

   [[nodiscard]] const std::string &getFirstName() const;

   void setFirstName(std::string firstName);

   [[nodiscard]] const std::string &getLastName() const;

   void setLastName(std::string lastName);

   [[nodiscard]] const std::string &getInitials() const;

   void setInitials(std::string initials);

   void output(std::ostream &output) const;

   [[nodiscard]] auto operator<=>(const Person &) const;

   explicit operator std::string() const;

private:
   std::string firstName_;
   std::string lastName_;
   std::string initials_;
};

std::ostream &operator<<(std::ostream &os, const Person &person);

std::istream &operator>>(std::istream &is, Person &person);

Person operator ""_p(const char *fromStr, std::size_t);

namespace std
{
   template<>
   struct hash<Person>
   {
      std::size_t operator()(const Person &person) const
      {
         std::size_t hashSeed = 17;
         hashSeed = hashSeed * 31 + std::hash<std::string>()(person.getFirstName());
         hashSeed = hashSeed * 31 + std::hash<std::string>()(person.getLastName());

         return hashSeed;
      }
   };
}
