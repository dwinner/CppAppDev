#ifndef PERSONSAMPLE_PERSON_HPP
#define PERSONSAMPLE_PERSON_HPP

#include <string>
#include <ostream>

namespace hr
{
   class Person final
   {
   public:
      Person();

      explicit Person(const std::string& firstName, const std::string& lastName);

      explicit Person(std::string firstName, std::string lastName, std::string initials);

      Person(const Person& src);

      Person& operator=(const Person& rhs);

      Person(Person&& src) noexcept;

      Person& operator=(Person&& rhs) noexcept;

      inline const std::string& getFirstName() const;

      inline void setFirstName(const std::string& firstName);

      inline const std::string& getLastName() const;

      inline void setLastName(const std::string& lastName);

      inline const std::string& getInitials() const;

      inline void setInitials(const std::string& initials);

      //void swap(Person& other) noexcept;

      ~Person();

      friend bool operator==(const Person& lhs, const Person& rhs);

      friend bool operator!=(const Person& lhs, const Person& rhs);

      friend bool operator<(const Person& lhs, const Person& rhs);

      friend bool operator>(const Person& lhs, const Person& rhs);

      friend bool operator<=(const Person& lhs, const Person& rhs);

      friend bool operator>=(const Person& lhs, const Person& rhs);

      friend std::ostream& operator<<(std::ostream& ostream, const Person& person);

      //friend void Swap(Person& first, Person& second) noexcept;

   private:
      /*friend*/ class Impl;
      std::unique_ptr<Impl> impl_;
   };
}

#endif //PERSONSAMPLE_PERSON_HPP
