#include <iostream>
#include <format>

using namespace std;

class Foo
{
public:
   Foo(double value);

private:
   double m_value{0};
};

Foo::Foo(double value) : m_value{value}
{
   cout << format("Foo::m_value = {}", m_value) << endl;
}

class MyClass
{
public:
   MyClass(double value);

private:
   Foo m_foo;
   double m_value{0};
};

MyClass::MyClass(double value)
    : m_value{value}, m_foo{m_value}
{
   cout << format("MyClass::m_value = {}", m_value) << endl;
}

int main()
{
   MyClass instance{1.2};
   return 0;
}
