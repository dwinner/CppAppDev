#include <iostream>
#include "InstalledPrograms.h"

using namespace std;
using namespace programList;

int main()
{
	vector<SoftwareEntity>* list = InstalledPrograms::GetInstalledPrograms(false);
	for (auto iter = list->begin(); iter != list->end(); ++iter)
	{
		cout << iter->DisplayName << "  "
			<< iter->InstallLocation << "  "
			<< iter->Version << "  "
			<< iter->Icon
			<< "  " << iter->Architecture << endl;
	}
}
