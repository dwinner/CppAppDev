export module person;

import std;

// Class definition
export class Person
{
public:
    explicit Person(std::string firstName, std::string lastName);

    const std::string& getFirstName() const;

    const std::string& getLastName() const;

private:
    std::string firstName_;
    std::string lastName_;
};

// Implementations
Person::Person(std::string firstName, std::string lastName)
    : firstName_{std::move(firstName)},
      lastName_{std::move(lastName)}
{
}

const std::string& Person::getFirstName() const
{
    return firstName_;
}

const std::string& Person::getLastName() const
{
    return lastName_;
}
