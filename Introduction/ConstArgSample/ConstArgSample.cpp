// ConstArgSample.cpp : Константный аргумент.

#include "stdafx.h"

void mysteryFunction(const char* myString)
{
   // Error: myString[0] = 'b';
}

int main()
{
   char* myString = new char[2];
   myString[0] = 'a';
   myString[1] = '\0';
   mysteryFunction(myString);

   return 0;
}

