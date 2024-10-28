export module person;

import std;

export class Person
{
public:
   // Two-parameter constructor automatically creates initials.
   // 
   // Warning: delegating to the 3-parameter constructor as follows doesn't work:
   //		Person(std::string firstName, std::string lastName)
   //			: Person{ std::move(firstName), std::move(lastName),
   //			std::format("{}{}", firstName[0], lastName[0]) }
   // because then firstName and lastName could already have been moved into
   // temporary std::strings before firstName[O] and lastName[O] are used in
   // the call to std::format().
   explicit Person(std::string firstName, std::string lastName):
      firstName_{std::move(firstName)},
      lastName_{std::move(lastName)}
   {
      initials_ = std::format("{}{}", firstName_[0], lastName_[0]);
   }

   Person() = default;

   explicit Person(std::string firstName, std::string lastName, std::string initials):
      firstName_{std::move(firstName)},
      lastName_{std::move(lastName)},
      initials_{std::move(initials)}
   {
   }

   const std::string& getFirstName() const
   {
      return firstName_;
   }

   void setFirstName(std::string firstName)
   {
      firstName_ = std::move(firstName);
   }

   const std::string& getLastName() const
   {
      return lastName_;
   }

   void setLastName(std::string lastName)
   {
      lastName_ = std::move(lastName);
   }

   const std::string& getInitials() const
   {
      return initials_;
   }

   void setInitials(std::string initials)
   {
      initials_ = std::move(initials);
   }

   void output(std::ostream& output) const
   {
      std::println(output, "{} {} ({})",
                   getFirstName(),
                   getLastName(),
                   getInitials());
   }

   // Only this single line of code is needed to add support
   // for all six comparison operators.
   [[nodiscard]] auto operator<=>(const Person&) const = default;

private:
   std::string firstName_;
   std::string lastName_;
   std::string initials_;
};
