// VectorSample.cpp: Использование STL-контейнеров.

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	// Создать вектор из строк, используя синтаксис инициализации C++11
	vector<string> myVector = { "a first string","A second string" };

	// Добавить некоторые строки в вектор
	myVector.push_back("A third string");
	myVector.push_back("The last string in the vector");

	// Итерирование по вектору
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

