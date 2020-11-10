#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <exception>

using namespace std;

void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;

	istr.open(fileName.c_str());
	if (istr.fail()) {
		// We failed to open the file: throw an exception
		throw exception();
	}

	// Read the integers one-by-one and add them to the vector
	while (istr >> temp) {
		dest.push_back(temp);
	}
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";

	try {
		readIntegerFile(fileName, myInts);
	} catch (exception /* e */) {
		cerr << "Unable to open file " << fileName << endl;
		return 1;
	}

	for (const auto element : myInts) {
		cout << element << " ";
	}
	cout << endl;

	return 0;
}
