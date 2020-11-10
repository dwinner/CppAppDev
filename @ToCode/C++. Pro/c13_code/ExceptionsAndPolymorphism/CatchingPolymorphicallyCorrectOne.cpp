#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;

	istr.open(fileName.c_str());
	if (istr.fail()) {
		// We failed to open the file: throw an exception
		string error = "Unable to open file " + fileName;
		throw invalid_argument(error);
	}

	// Read the integers one-by-one and add them to the vector
	while (istr >> temp) {
		dest.push_back(temp);
	}

	if (!istr.eof()) {
		// We did not reach the end-of-file.
		// This means that some error occurred while reading the file.
		// Throw an exception.
		string error = "Unable to read file " + fileName;
		throw runtime_error(error);
	}
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";

	try {
		readIntegerFile(fileName, myInts);
	} catch (const exception& e) {
		cerr << e.what() << endl;
		return 1;
	}

	for (const auto element : myInts) {
		cout << element << " ";
	}
	cout << endl;

	return 0;
}
