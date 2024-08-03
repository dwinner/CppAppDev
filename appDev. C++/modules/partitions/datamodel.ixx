export module datamodel; // datamodel module (primary module interface file)

export import :person;   // Import and export person partition
export import :address;  // Import and export address partition

import std;

export namespace dataModel
{
    using Persons = std::vector<Person>;
}
