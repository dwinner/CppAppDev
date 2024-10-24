import std;
import emp;

namespace empNs
{
   Person::Person(const std::string& firstName, const std::string& lastName) :
      Person
      {
         firstName,
         lastName,
         extractInitials(firstName, lastName)
      }
   {
   }

   Person::Person() : Person{"", "", ""}
   {
   }

   Person::Person(const Person& src) = default;

   Person& Person::operator=(const Person& rhs) = default;

   inline const std::string& Person::getFirstName() const
   {
      return firstName_;
   }

   void Person::setFirstName(const std::string& firstName)
   {
      firstName_ = firstName;
   }

   inline const std::string& Person::getLastName() const
   {
      return lastName_;
   }

   void Person::setLastName(const std::string& lastName)
   {
      lastName_ = lastName;
   }

   const std::string& Person::getInitials() const
   {
      return initials_;
   }

   void Person::setInitials(const std::string& initials)
   {
      initials_ = initials;
   }

   Person::Person(std::string firstName, std::string lastName, std::string initials)
      : firstName_(std::move(firstName)),
        lastName_(std::move(lastName)),
        initials_(std::move(initials))
   {
   }

   std::string Person::extractInitials(const std::string& firstName, const std::string& lastName)
   {
      std::string initials;
      if (!firstName.empty())
      {
         initials += static_cast<char>(std::toupper(firstName[0]));
      }

      if (!lastName.empty())
      {
         initials += static_cast<char>(std::toupper(lastName[0]));
      }

      return initials;
   }

   Person::~Person() = default;

   std::ostream& operator<<(std::ostream& ostream, const Person& person)
   {
      ostream <<
         "First name: " << person.getFirstName() <<
         ", Last name: " << person.getLastName() <<
         ", Initials: " << person.getInitials();
      return ostream;
   }
}

/**
 * Global string representation for Person
 */
template <>
class std::formatter<empNs::Person>
{
public:
   constexpr auto parse(auto& context)
   {
      return begin(context);
   }

   auto format(const empNs::Person& person, auto& context) const
   {
      context.advance_to(
         format_to(
            context.out(),
            "First name - {}, Last name - {}",
            person.getFirstName(),
            person.getLastName())
      );
      return context.out();
   }
};
