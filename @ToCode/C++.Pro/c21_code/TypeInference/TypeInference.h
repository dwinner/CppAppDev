#pragma once

#include <string>

// Forward class declaration
class MyString;

class MyInt
{
public:
	MyInt(int i) : mValue(i) {}
	MyInt operator+(const MyString& rhs) const;
	int getInt() const { return mValue; }

private:
	int mValue;
};

class MyString
{
public:
	MyString(const std::string& str) : mString(str) {}
	MyString operator+(const MyInt& rhs) const;
	const std::string& getString() const { return mString; }

private:
	std::string mString;
};
