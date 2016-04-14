// StdArraySample.cpp : Массивы стандартной библиотеки.

#include "stdafx.h"
#include <array>
#include <iostream>

using namespace std;

int main()
{
   array<int, 3> arr = { 9,8,7 };
   cout << "Array size = " << arr.size() << endl;
   for (auto iter = arr.begin(); iter != arr.end(); ++iter)
   {
      cout << *iter << endl;
   }

   return 0;
}

