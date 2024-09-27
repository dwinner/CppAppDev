#pragma once

#include <string>
#include <ostream>

class Person final
{
public:
   Person();

   explicit Person(const std::string& firstName, const std::string& lastName);

   explicit Person(std::string firstName, std::string lastName, std::string initials);

   Person(const Person&);

   Person& operator=(const Person&);

   Person(Person&&) noexcept;

   Person& operator=(Person&&) noexcept;

   [[nodiscard]] const std::string& getFirstName() const &
   {
      return firstName_;
   }

   [[nodiscard]] std::string&& getFirstName() &&
   {
      return std::move(firstName_);
   }

   void setFirstName(const std::string& firstName)
   {
      firstName_ = firstName;
   }

   [[nodiscard]] const std::string& getLastName() const &
   {
      return lastName_;
   }

   [[nodiscard]] std::string&& getLastName() &&
   {
      return std::move(lastName_);
   }

   void setLastName(const std::string& lastName)
   {
      lastName_ = lastName;
   }

   [[nodiscard]] const std::string& getInitials() const &
   {
      return initials_;
   }

   [[nodiscard]] std::string&& getInitials() &&
   {
      return std::move(initials_);
   }

   void setInitials(const std::string& initials)
   {
      initials_ = initials;
   }

   ~Person();

private:
   [[nodiscard]] static std::string extractInitials(const std::string& firstName, const std::string& lastName);

   std::string firstName_;
   std::string lastName_;
   std::string initials_;
};


std::ostream& operator<<(std::ostream& ostream, const Person& person);
