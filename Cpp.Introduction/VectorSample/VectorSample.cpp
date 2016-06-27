// VectorSample.cpp: ������������� STL-�����������.

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	// ������� ������ �� �����, ��������� ��������� ������������� C++11
	vector<string> myVector = { "a first string","A second string" };

	// �������� ��������� ������ � ������
	myVector.push_back("A third string");
	myVector.push_back("The last string in the vector");

	// ������������ �� �������
	for (auto iterator = myVector.cbegin(); iterator != myVector.cend(); ++iterator)
	{
		cout << *iterator << endl;
	}

	for (auto& str : myVector)
	{
		cout << str << endl;
	}

	return 0;
}

