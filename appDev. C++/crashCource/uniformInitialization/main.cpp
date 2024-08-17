#include <iostream>
#include <vector>
#include "Types.h"

using namespace std;

void func(int i) { /* ... */ }

void initEmp(){
   // Initialize all data members
   Employee anEmployee1{
       .firstInitial = 'J',
       .lastInitial = 'D',
       .employeeNumber = 42,
       .salary = 80'000
   };

   // Initialize all data members, except employeeNumber
   Employee anEmployee2{
       .firstInitial = 'J',
       .lastInitial = 'D',
       .salary = 80'000
   };

   // Initialize all data members, except employeeNumber, and salary
   Employee anEmployee3{
       .firstInitial = 'J',
       .lastInitial = 'D'
   };
}

int main()
{
   // Old pre-C++11 way
   CircleStruct myCircle1 = {10, 10, 2.5};
   CircleClass myCircle2(10, 10, 2.5);

   // C++11 uniform initialization
   CircleStruct myCircle3 = {10, 10, 2.5};
   CircleClass myCircle4 = {10, 10, 2.5};
   CircleStruct myCircle5{10, 10, 2.5};
   CircleClass myCircle6{10, 10, 2.5};

   // Initializing a struct
   Employee anEmployee;
   anEmployee.firstInitial = 'J';
   anEmployee.lastInitial = 'D';
   anEmployee.employeeNumber = 42;
   anEmployee.salary = 80'000;

   // Initializing a struct with uniform initialization
   Employee anEmployee2{ 'J', 'D', 42, 80'000 };

   int a = 3;
   int b(3);
   int c = { 3 }; // Uniform initialization
   int d{ 3 };    // Uniform initialization

   int e{};       // Uniform initialization, e will be 0

   Employee anEmployee3;
   Employee anEmployee4{ };

   // Narrowing
   int x = 3.14;
   func(3.14);

   // Preventing narrowing
   //int x{3.14};       // Error because narrowing
   //func({3.14});      // Error because narrowing

   // Create a MyClass object
   MyClass myClass;

   // Uniform initialization also works with vectors
   vector<string> myVec{"String 1", "String 2", "String 3"};
   return 0;
}
