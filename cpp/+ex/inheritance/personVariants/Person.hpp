#pragma once

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

      [[nodiscard]] inline const std::string &getLastName() const;

      [[nodiscard]] inline const std::string &getInitials() const;

      virtual ~Person();

      bool operator==(const Person &rhs) const;

      std::partial_ordering operator<=>(const Person &rhs);

      friend std::ostream &operator<<(std::ostream &ostream, const Person &person);

      [[nodiscard]] virtual std::string toString() const;

      [[nodiscard]] virtual std::string getClsName() const;

   private:
      [[nodiscard]] static std::string extractInitials(const std::string &firstName, const std::string &lastName);

      std::string firstName_;
      std::string lastName_;
      std::string initials_;
   };
}
