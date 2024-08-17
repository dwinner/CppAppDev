#include <iostream>
#include <cstddef>
#include <format>
#include "misc.h"

using namespace std;

void arrayPtr()
{
   int arraySize{8};
   int *myVariableSizedArray{new int[arraySize]};
   myVariableSizedArray[3] = 2;
   delete[] myVariableSizedArray;
   myVariableSizedArray = nullptr;
}

int main()
{
   func(NULL);
   //func(nullptr); // Compilation error.

   {
      int *myIntegerPointer{nullptr};
      if (!myIntegerPointer)
      { /* myIntegerPointer is a null pointer */ }
      myIntegerPointer = new int;
      *myIntegerPointer = 8;
      delete myIntegerPointer;
      myIntegerPointer = nullptr;
   }

   {
      int i{8};
      int *myIntegerPointer{&i};  // Points to the variable with the value 8
   }


   {
      Employee *anEmployee
          {
              new Employee
                  {
                      'J',
                      'D',
                      42,
                      80'000
                  }
          };

      cout << std::format("{}", (*anEmployee).salary) << endl;
      cout << std::format("{}", anEmployee->salary) << endl;

      bool isValidSalary1{anEmployee && anEmployee->salary > 0};
      bool isValidSalary2{anEmployee != nullptr && anEmployee->salary > 0};

      delete anEmployee;
      anEmployee = nullptr;
   }

   return 0;
}
