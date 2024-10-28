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

      bool operator==(const Person &rhs) const;

      std::partial_ordering operator<=>(const Person & rhs);

      friend void swap(Person &first, Person &second) noexcept;

      friend std::ostream &operator<<(std::ostream &ostream, const Person &person);

   private:
      [[nodiscard]] static std::string extractInitials(const std::string &firstName, const std::string &lastName);

      std::string firstName_;
      std::string lastName_;
      std::string initials_;
   };
}

#endif //PERSONSAMPLE_PERSON_HPP
