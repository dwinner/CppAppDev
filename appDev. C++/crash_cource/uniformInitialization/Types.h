#ifndef UNIFORMINITIALIZATION_TYPES_H
#define UNIFORMINITIALIZATION_TYPES_H

struct Employee
{
   char firstInitial{' '};
   char lastInitial{' '};
   int employeeNumber{-1};
   int salary{75'000};
};

struct CircleStruct
{
   int x, y;
   double radius;
};

class CircleClass
{
public:
   CircleClass(int x, int y, double radius)
       : m_x{x}, m_y{y}, m_radius{radius}
   {}

private:
   int m_x, m_y;
   double m_radius;
};

class MyClass
{
public:
   MyClass() : m_array{0, 1, 2, 3}
   {}

private:
   int m_array[4];
};

#endif //UNIFORMINITIALIZATION_TYPES_H
