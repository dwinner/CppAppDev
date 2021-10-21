#include <algorithm>
#include <iostream>
#include "InstalledPrograms.h"

int main()
{
	using namespace std;
	using namespace programList;

	vector<SoftwareEntity>* softwareList = InstalledPrograms::GetInstalledPrograms(false);
	/*for (auto iter = softwareList->begin(); iter != softwareList->end(); ++iter)
	{
		cout << iter->DisplayName << "  "
			<< iter->InstallLocation << "  "
			<< iter->Version << "  "
			<< iter->Icon
			<< "  " << iter->Architecture << endl;
	}*/

	// Search 'Visual Studio Code'
	string vsCodeSwName = "Visual Studio Code";
	const auto iter = find_if(
		softwareList->begin(),
		softwareList->end(),
		[&vsCodeSwName](const SoftwareEntity& swEntity)
		{
			const size_t findPos = swEntity.DisplayName.find(vsCodeSwName);
			return findPos != string::npos
				       ? swEntity.InstallLocation.empty()
					         // also check install location, if a user deleted program manually
					         ? false
					         : true
				       : false;
		});

	// found
	if (iter != softwareList->end())
	{
		const auto vsCode = *iter;
		cout << "Display name: " << vsCode.DisplayName << endl
			<< "Version: " << vsCode.Version << endl
			<< "Install location: " << vsCode.InstallLocation << endl
			<< "Launch path: " << vsCode.Icon << endl;
	}
}
