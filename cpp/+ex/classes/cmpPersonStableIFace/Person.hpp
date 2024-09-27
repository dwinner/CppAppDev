#pragma once

#include <string>
#include <ostream>

namespace hr
{
   class Person final
   {
   public:
      Person();

      explicit Person(const std::string& firstName, const std::string& lastName);

      explicit Person(const std::string& firstName, const std::string& lastName, const std::string& initials);

      Person(const Person& src);

      Person& operator=(const Person& rhs);

      Person(Person&& src) noexcept;

      Person& operator=(Person&& rhs) noexcept;

      [[nodiscard]] inline const std::string& getFirstName() const;

      inline void setFirstName(const std::string& firstName) const;

      [[nodiscard]] inline const std::string& getLastName() const;

      inline void setLastName(const std::string& lastName) const;

      [[nodiscard]] inline const std::string& getInitials() const;

      inline void setInitials(const std::string& initials) const;

      ~Person();

      friend bool operator==(const Person& lhs, const Person& rhs);

      friend bool operator!=(const Person& lhs, const Person& rhs);

      friend bool operator<(const Person& lhs, const Person& rhs);

      friend bool operator>(const Person& lhs, const Person& rhs);

      friend bool operator<=(const Person& lhs, const Person& rhs);

      friend bool operator>=(const Person& lhs, const Person& rhs);

      friend std::ostream& operator<<(std::ostream& ostream, const Person& person);

   private:
      class Impl;
      std::unique_ptr<Impl> impl_;
   };
}
