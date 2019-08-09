#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>

using namespace std;

class FileError : public exception
{
public:
	FileError(const string& fileIn) : mFile(fileIn) {}
	virtual const char* what() const noexcept override { return mMsg.c_str(); }
	const string& getFileName() { return mFile; }

protected:
	void setMessage(const string& message) { mMsg = message; }

private:
	string mFile, mMsg;
};

class FileOpenError : public FileError
{
public:
	FileOpenError(const string& fileNameIn);
};

FileOpenError::FileOpenError(const string& fileNameIn) : FileError(fileNameIn)
{
	setMessage("Unable to open " + fileNameIn);
}

class FileReadError : public FileError
{
public:
	FileReadError(const string& fileNameIn, int lineNumIn);
	int getLineNum() { return mLineNum; }

private:
	int mLineNum;
};

FileReadError::FileReadError(const string& fileNameIn, int lineNumIn) :
FileError(fileNameIn), mLineNum(lineNumIn)
{
	ostringstream ostr;

	ostr << "Error reading " << fileNameIn << " at line " << lineNumIn;
	setMessage(ostr.str());
}

void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;
	string line;
	int lineNumber = 0;

	istr.open(fileName.c_str());
	if (istr.fail()) {
		// We failed to open the file: throw an exception
		throw FileOpenError(fileName);
	}

	while (!istr.eof()) {
		// Read one line from the file
		getline(istr, line);
		lineNumber++;

		// Create a string stream out of the line
		istringstream lineStream(line);

		// Read the integers one-by-one and add them to the vector
		while (lineStream >> temp) {
			dest.push_back(temp);
		}

		if (!lineStream.eof()) {
			// We did not reach the end of the string stream.
			// This means that some error occurred while reading this line.
			// Throw an exception.
			throw FileReadError(fileName, lineNumber);
		}
	}
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";

	try {
		readIntegerFile(fileName, myInts);
	} catch (const FileError& e) {
		cerr << e.what() << endl;
		return 1;
	}

	for (const auto element : myInts) {
		cout << element << " ";
	}
	cout << endl;

	return 0;
}
