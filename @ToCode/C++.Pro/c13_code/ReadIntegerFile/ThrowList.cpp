#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Note:
//  The use of throw lists has been deprecated since C++11.

void readIntegerFile(const string& fileName, vector<int>& dest) throw (invalid_argument, runtime_error);

void readIntegerFile(const string& fileName, vector<int>& dest) throw (invalid_argument, runtime_error)
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

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";

	try {
		readIntegerFile(fileName, myInts);
	} catch (const invalid_argument& e) {
		cerr << e.what() << endl;
		return 1;
	} catch (const runtime_error& e) {
		cerr << e.what() << endl;
		return 1;
	}

	for (const auto element : myInts) {
		cout << element << " ";
	}
	cout << endl;

	return 0;
}
