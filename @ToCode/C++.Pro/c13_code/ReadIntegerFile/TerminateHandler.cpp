#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <exception>

using namespace std;

void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;

	istr.open(fileName.c_str());
	if (istr.fail()) {
		// We failed to open the file: throw an exception
		throw invalid_argument("Unable to open the file.");
	}

	// Read the integers one-by-one and add them to the vector
	while (istr >> temp) {
		dest.push_back(temp);
	}

	if (!istr.eof()) {
		// We did not reach the end-of-file.
		// This means that some error occurred while reading the file.
		// Throw an exception.
		throw runtime_error("Error reading the file.");
	}
}

void myTerminate()
{
	cout << "Uncaught exception!" << endl;
	exit(1);
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";

	set_terminate(myTerminate);

	readIntegerFile(fileName, myInts);

	for (const auto element : myInts) {
		cout << element << " ";
	}
	cout << endl;

	return 0;
}
