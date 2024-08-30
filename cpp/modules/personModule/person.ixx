export module person;

import std;

export class Person
{
public:
    explicit Person(std::string firstName, std::string lastName) :
        firstName_{ std::move(firstName) },
        lastName_{ std::move(lastName) }
    {
    }

    const std::string& getFirstName() const
    {
        return firstName_;
    }

    const std::string& getLastName() const
    {
        return lastName_;
    }

private:
    std::string firstName_;
    std::string lastName_;
};
