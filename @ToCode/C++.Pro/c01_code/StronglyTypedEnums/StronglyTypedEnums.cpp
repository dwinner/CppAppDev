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

int main()
{
	MyEnum value1 = MyEnum::EnumValue1;
	return 0;
}
