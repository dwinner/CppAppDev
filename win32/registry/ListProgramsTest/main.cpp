#include <iostream>
#include "InstalledPrograms.h"

using namespace std;
using namespace programList;

int main()
{
	vector<SoftwareEntity>* list = InstalledPrograms::GetInstalledPrograms(false);
	for (auto iter = list->begin(); iter != list->end(); ++iter)
	{
		wcout << iter->DisplayName << L"  "
			<< iter->InstallLocation << L"  "
			<< iter->Version << L"  "
			<< iter->Icon
			<< L"  " << iter->Architecture << endl;
	}
}
