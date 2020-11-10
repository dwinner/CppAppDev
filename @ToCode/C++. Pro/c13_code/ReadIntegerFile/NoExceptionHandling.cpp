#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;

	istr.open(fileName.c_str());

	// Read the integers one-by-one and add them to the vector.
	while (istr >> temp) {
		dest.push_back(temp);
	}
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";

	readIntegerFile(fileName, myInts);

	for (const auto element : myInts) {
		cout << element << " ";
	}
	cout << endl;

	return 0;
}
