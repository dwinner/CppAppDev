module person;

Person::Person(const std::string& firstName, const std::string& lastName)
   : Person{firstName, lastName, extractInitials(firstName, lastName)}
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

std::istream& operator>>(std::istream& iStream, Person& person)
{
   std::string fName, lName;
   iStream >> fName;
   iStream >> lName;
   person.setFirstName(fName);
   person.setLastName(lName);

   return iStream;
}
