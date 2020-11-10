#include "01_FirstAttempt/ArticleCitations.h"
#include <iostream>
#include <exception>
using namespace std;

void processCitations(ArticleCitations cit)
{
	cout << cit.getArticle() << endl;
	int num = cit.getNumCitations();
	for (int i = 0; i < num; i++) {
		cout << cit.getCitation(i) << endl;
	}
}

int main()
{
	string fileName;

	while (true) {
		cout << "Enter a file name (\"STOP\" to stop): ";
		cin >> fileName;

		if (fileName == "STOP") {
			break;
		}
		try {
			// Test constructor
			ArticleCitations cit(fileName);
			processCitations(cit);
		} catch (const exception& ex) {
			cout << ex.what() << endl;
		}
	}

	return 0;
}
