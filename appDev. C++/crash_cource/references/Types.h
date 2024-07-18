#ifndef REFERENCES_TYPES_H
#define REFERENCES_TYPES_H

#include <string>
#include <iostream>
#include <format>

class MyClass
{
public:
   MyClass(int &ref) : m_ref{ref}
   { /* Body of constructor */ }

private:
   int &m_ref;
};

void addOneA(int i)
{
   i++;  // Has no real effect because this is a copy of the original
}

void addOneB(int &i)
{
   i++;  // Actually changes the original variable
}

void swap(int &first, int &second)
{
   int temp{first};
   first = second;
   second = temp;
}

void printString(const std::string &myString)
{
   std::cout << std::format("{}", myString) << std::endl;
}

#endif //REFERENCES_TYPES_H
