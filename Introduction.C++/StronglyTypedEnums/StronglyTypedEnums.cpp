// StronglyTypedEnums.cpp : ������ �������������� ������������.

#include "stdafx.h"

int main()
{
   return 0;
}

enum class MyEnum
{
   EnumValue1,
   EnumValue2 = 10,
   EnumValue3
};

enum class MyEnumLong : unsigned long
{
   EnumValueLong1,
   EnumValueLong2 = 10,
   EnumValueLong3
};

