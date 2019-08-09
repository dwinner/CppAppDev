#include <iostream>
#include <memory>
#include <cstdio>
using namespace std;

void CloseFile(FILE* filePtr)
{
	if (filePtr == nullptr)
		return;
	fclose(filePtr);
	cout << "File closed." << endl;
}

int main()
{
	FILE* f = nullptr;
	fopen_s(&f, "data.txt", "w");
	shared_ptr<FILE> filePtr(f, CloseFile);
	if (filePtr == nullptr) {
		cerr << "Error opening file." << endl;
	} else {
		cout << "File opened." << endl;
		// Use filePtr
	}
	return 0;
}
