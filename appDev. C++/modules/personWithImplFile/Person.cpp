module person;

import std;
using namespace std;

Person::Person(string firstName, string lastName)
    : firstName_{move(firstName)},
      lastName_{move(lastName)}
{
}

const string& Person::getFirstName() const
{
    return firstName_;
}

const string& Person::getLastName() const
{
    return lastName_;
}
