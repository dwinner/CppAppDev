#include "ArticleCitations.h"
#include <iostream>
using namespace std;

void processCitations(ArticleCitations cit);

int main()
{
	string fileName;

	while (true) {
		cout << "Enter a file name (\"STOP\" to stop): ";
		cin >> fileName;

		if (fileName == "STOP") {
			break;
		}
		// Test constructor
		ArticleCitations cit(fileName);
		processCitations(cit);
	}

	return 0;
}

void processCitations(ArticleCitations cit)
{
	cout << cit.getArticle() << endl;
	int num = cit.getNumCitations();
	for (int i = 0; i < num; i++) {
		cout << cit.getCitation(i) << endl;
	}
}
