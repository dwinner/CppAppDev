#ifndef PERSONSAMPLE_PERSON_HPP
#define PERSONSAMPLE_PERSON_HPP

#include <string>
#include <ostream>

namespace HR
{
   class Person
   {
   public:
      Person();

      explicit Person(const std::string &firstName, const std::string &lastName);

      explicit Person(std::string firstName, std::string lastName, std::string initials);

      Person(const Person &src);

      Person &operator=(const Person &rhs);

      Person(Person &&src) noexcept;

      Person &operator=(Person &&rhs) noexcept;

      [[nodiscard]] inline const std::string &getFirstName() const;

      void setFirstName(const std::string &firstName);

      [[nodiscard]] inline const std::string &getLastName() const;

      void setLastName(const std::string &lastName);

      [[nodiscard]] inline const std::string &getInitials() const;

      void setInitials(const std::string &initials);

      void swap(Person &other) noexcept;

      virtual ~Person();

      friend bool operator==(const Person &lhs, const Person &rhs);

      friend bool operator!=(const Person &lhs, const Person &rhs);

      friend bool operator<(const Person &lhs, const Person &rhs);

      friend bool operator>(const Person &lhs, const Person &rhs);

      friend bool operator<=(const Person &lhs, const Person &rhs);

      friend bool operator>=(const Person &lhs, const Person &rhs);

      friend std::ostream &operator<<(std::ostream &ostream, const Person &person);

      friend void swap(Person &first, Person &second);

   private:
      [[nodiscard]] static std::string extractInitials(const std::string &firstName, const std::string &lastName);

      std::string firstName_;
      std::string lastName_;
      std::string initials_;
   };
}

#endif //PERSONSAMPLE_PERSON_HPP
