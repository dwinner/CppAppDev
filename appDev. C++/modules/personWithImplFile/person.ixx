export module person;

import std;

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
