// InitializerListSample.cpp : Инициализаторы в конструкторах.

#include "stdafx.h"
#include <ostream>
#include <iostream>
#include "PointSequence.h"

int _tmain(int argc, _TCHAR* argv[])
{
   PointSequence p1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
   p1.dumpPoints();
   try
   {
      PointSequence p2 = { 1.0, 2.0, 3.0 };
   }
   catch (const std::invalid_argument &e)
   {
      std::cout << e.what() << std::endl;
   }

   return 0;
}

