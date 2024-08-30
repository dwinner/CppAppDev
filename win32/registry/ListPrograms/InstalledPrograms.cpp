#include "InstalledPrograms.h"
#include <algorithm>
#include <regex>
#include <utility>

namespace programList
{
	using namespace std;

	static wstring getInstallerKeyNameFromGuid(wstring guidName);

	static void addToList(vector<SoftwareEntity>* swList, SoftwareEntity software);

	SoftwareEntity::SoftwareEntity(wstring name, wstring version, wstring location, wstring icon, const Arch arch)
		: DisplayName(std::move(name)),
		  InstallLocation(std::move(location)),
		  Version(std::move(version)),
		  Architecture(arch),
		  Icon(std::move(icon))
	{
	}

	InstalledPrograms::InstalledPrograms() = default;

	InstalledPrograms::~InstalledPrograms() = default;

	vector<SoftwareEntity>* InstalledPrograms::GetInstalledPrograms(const bool includeUpdates)
	{
		return GetInstalledProgramsImp(includeUpdates);
	}

	vector<SoftwareEntity>* InstalledPrograms::GetInstalledProgramsImp(const bool includeUpdates)
	{
		auto softwareList = new vector<SoftwareEntity>();

		RegistryKey* classesKey = RegistryKey::GetHklmKey().OpenSubKey(L"Software\\Classes\\Installer\\Products");
		RegistryKey* wow64UninstallKey = RegistryKey::GetHklmKey().OpenSubKey32(
			L"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
		softwareList = GetUninstallKeyPrograms(wow64UninstallKey, classesKey, softwareList, includeUpdates);
		RegistryKey* uninstallKey = RegistryKey::GetHklmKey().OpenSubKey64(
			L"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
		softwareList = GetUninstallKeyPrograms(uninstallKey, classesKey, softwareList, includeUpdates);
		vector<wstring> subkeys = RegistryKey::GetHkuKey().GetSubKeyNames();

		for (auto it = subkeys.begin(); it != subkeys.end(); ++it)
		{
			wstring uninstallSubs = *it + L"\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall";
			RegistryKey* lUninstallKey = RegistryKey::GetHkuKey().OpenSubKey(uninstallSubs);
			softwareList = GetUninstallKeyPrograms(lUninstallKey, classesKey, softwareList, includeUpdates);
			delete lUninstallKey;

			wstring installersubs = *it + L"\\Software\\Microsoft\\Installer\\Products";
			RegistryKey* installerKey = RegistryKey::GetHkuKey().OpenSubKey(installersubs);
			softwareList = GetUserInstallerKeyPrograms(installerKey, softwareList);
			delete installerKey;
		}

		delete uninstallKey;
		delete wow64UninstallKey;
		delete classesKey;

		std::sort(softwareList->begin(), softwareList->end(), [](SoftwareEntity s1, SoftwareEntity s2)-> bool
		{
			std::transform(s1.DisplayName.begin(), s1.DisplayName.end(), s1.DisplayName.begin(), ::tolower);
			std::transform(s2.DisplayName.begin(), s2.DisplayName.end(), s2.DisplayName.begin(), ::tolower);
			return s1.DisplayName.compare(s2.DisplayName) < 0;
		});

		return softwareList;
	}

	vector<SoftwareEntity>* InstalledPrograms::GetUserInstallerKeyPrograms(
		RegistryKey* uInstallerKey,
		vector<SoftwareEntity>* existingProgramList)
	{
		if (uInstallerKey == nullptr)
		{
			return existingProgramList;
		}

		RegistryKey* userData32 = RegistryKey::GetHklmKey().OpenSubKey32(
			L"Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData");
		RegistryKey* userData64 = RegistryKey::GetHklmKey().OpenSubKey64(
			L"Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData");

		if (userData32 == nullptr && userData64 == nullptr)
		{
			return existingProgramList;
		}

		RegistryKey* userDataArray[2] = {userData32, userData64};
		for (auto userData : userDataArray)
		{
			if (userData == nullptr)
			{
				continue;
			}

			vector<wstring> subkeys = uInstallerKey->GetSubKeyNames();
			for (auto it = subkeys.begin(); it != subkeys.end(); ++it)
			{
				vector<wstring> userDataSubKeys = userData->GetSubKeyNames();
				bool productFound = false;

				for (auto userDataIter = userDataSubKeys.begin(); userDataIter != userDataSubKeys.end(); ++userDataIter)
				{
					// Ignore the LocalSystem account
					if (*userDataIter == L"S-1-5-18")
					{
						continue;
					}

					RegistryKey* productsKey = RegistryKey::GetHklmKey().OpenSubKey(
						wstring(L"Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\")
						.append(*userDataIter)
						.append(L"\\Products"), UnKnown);

					if (productsKey != nullptr)
					{
						vector<wstring> lmProductGuids = productsKey->GetSubKeyNames();
						for (auto productIter = lmProductGuids.begin(); productIter != lmProductGuids.end(); ++
						     productIter)
						{
							if (*productIter == *it)
							{
								RegistryKey* userDataProgramKey = RegistryKey::GetHklmKey().OpenSubKey(
									wstring(L"Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\")
									.append(*userDataIter)
									.append(L"\\Products\\")
									.append(*productIter)
									.append(L"\\InstallProperties"), UnKnown);
								if (userDataProgramKey != nullptr)
								{
									wstring sysCompValue = userDataProgramKey->GetValue(L"SystemComponent");
									if (sysCompValue.empty() || _wtoi(sysCompValue.c_str()) != 1)
									{
										RegistryKey* temp = uInstallerKey->OpenSubKey(*it, uInstallerKey->KeyArch);

										// Name 
										wstring productName = temp->GetValue(L"ProductName");
										wstring displayName = userDataProgramKey->GetValue(L"DisplayName");
										wstring swName = productName.empty() ? displayName : productName;

										// Version
										wstring progVersion = userDataProgramKey->GetValue(L"DisplayVersion");

										// InstallLocation
										wstring installLocation = userDataProgramKey->GetValue(L"InstallLocation");

										// Icon
										wstring productIcon = temp->GetValue(L"ProductIcon");
										wstring displayIcon = userDataProgramKey->GetValue(L"DisplayIcon");
										wstring icon = productIcon.empty() ? displayIcon : productIcon;

										if (!swName.empty())
										{
											addToList(existingProgramList,
											          SoftwareEntity(swName,
											                         progVersion,
											                         installLocation,
											                         icon,
											                         userData->KeyArch));
											productFound = true; // NOTE: here the correct place for using 'goto'
										}

										delete temp;
									}

									delete userDataProgramKey;
								}

								break;
							}
						}

						if (productFound)
						{
							break;
						}

						delete productsKey;
					}
				}
			}

			delete userData;
		}

		return existingProgramList;
	}

	vector<SoftwareEntity>* InstalledPrograms::GetUninstallKeyPrograms(RegistryKey* uninstallKey,
	                                                                   RegistryKey* classesKey,
	                                                                   vector<SoftwareEntity>* ExistingProgramList,
	                                                                   bool includeUpdates)
	{
		// Make sure the key exists
		if (uninstallKey != nullptr)
		{
			// Loop through all subkeys (each one represents an installed program)
			vector<wstring> uninstallSubKeys = uninstallKey->GetSubKeyNames();
			for (auto subKeyName = uninstallSubKeys.begin(); subKeyName != uninstallSubKeys.end(); ++subKeyName)
			{
				RegistryKey* currentSubKey = uninstallKey->OpenSubKey(*subKeyName, uninstallKey->KeyArch);
				if (currentSubKey == nullptr)
				{
					continue;
				}

				int isSystemComponent = 1;
				wstring sysCompValue = currentSubKey->GetValue(L"SystemComponent");
				if (sysCompValue.empty() || _wtoi(sysCompValue.c_str()) != 1)
				{
					isSystemComponent = 0;
				}

				if (isSystemComponent != 1)
				{
					wstring winInstallerVal = currentSubKey->GetValue(L"WindowsInstaller");

					// If the WindowsInstaller flag is set then add the key name to our list of Windows Installer GUIDs
					if (winInstallerVal.empty() || _wtoi(winInstallerVal.c_str()) != 1)
					{
						wregex windowsUpdateRegEx(L"KB[0-9]{6}$");

						// Release Type
						wstring programReleaseType = currentSubKey->GetValue(L"ReleaseType");

						// Version
						wstring progVersion = currentSubKey->GetValue(L"DisplayVersion");

						// Name 
						wstring displayName = currentSubKey->GetValue(L"DisplayName");

						// InstallLocation
						wstring installLocation = currentSubKey->GetValue(L"InstallLocation");

						// Icon
						wstring icon = currentSubKey->GetValue(L"DisplayIcon");

						auto parentKeyName = currentSubKey->GetValue(L"ParentKeyName");

						// Check to see if this program is classed as an update
						if (regex_match(*subKeyName, windowsUpdateRegEx) == true
							|| !parentKeyName.empty()
							|| programReleaseType == L"Security Update"
							|| programReleaseType == L"Update Rollup"
							|| programReleaseType == L"Hotfix")
						{
							// Add the program to our list if we are including updates in this search
							if (includeUpdates && !displayName.empty())
							{
								addToList(ExistingProgramList,
								          SoftwareEntity(displayName,
								                         progVersion,
								                         installLocation,
								                         icon,
								                         uninstallKey->KeyArch));
							}
						}
						else
						{
							wstring uninstallValue = currentSubKey->GetValue(L"UninstallString");
							if (!uninstallValue.empty() && !displayName.empty())
							{
								addToList(ExistingProgramList,
								          SoftwareEntity(displayName,
								                         progVersion,
								                         installLocation,
								                         icon,
								                         uninstallKey->KeyArch));
							}
						}
					}
					else
					{
						// If WindowsInstaller

						// Name
						wstring productName;
						wstring productItem;
						wstring msiKeyName = getInstallerKeyNameFromGuid(*subKeyName);
						RegistryKey* crGuidKey = classesKey->OpenSubKey(msiKeyName, classesKey->KeyArch);
						if (crGuidKey != nullptr)
						{
							productName = crGuidKey->GetValue(L"ProductName");
							productItem = crGuidKey->GetValue(L"ProductIcon");
							delete crGuidKey;
						}

						wstring displayName = currentSubKey->GetValue(L"DisplayName");
						wstring swName = productName.empty() ? displayName : productName;

						// Version
						wstring progVersion = currentSubKey->GetValue(L"DisplayVersion");

						// InstallLocation
						wstring installLocation = currentSubKey->GetValue(L"InstallLocation");

						// Icon
						wstring displayIcon = currentSubKey->GetValue(L"DisplayIcon");
						wstring icon = productItem.empty() ? displayIcon : productItem;
						if (!swName.empty())
						{
							addToList(ExistingProgramList,
							          SoftwareEntity(swName,
							                         progVersion,
							                         installLocation,
							                         icon,
							                         uninstallKey->KeyArch));
						}
					}
				}
			}
		}

		return ExistingProgramList;
	}

	// Util Functions
	static void addToList(vector<SoftwareEntity>* swList, SoftwareEntity software)
	{
		int index = -1;
		for (int i = 0; i < static_cast<int>(swList->size()); i++)
		{
			if (swList->at(i).DisplayName == software.DisplayName)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
		{
			swList->push_back(software);
		}
		else
		{
			const SoftwareEntity duplicate = swList->at(index);

			// Merge Architecture
			if (software.Architecture != UnKnown
				&& duplicate.Architecture != UnKnown
				&& duplicate.Architecture != software.Architecture)
			{
				swList->push_back(software);
				return;
			}

			if (software.Architecture == UnKnown)
			{
				software.Architecture = duplicate.Architecture;
			}

			// Merge Icon
			if (!software.Icon.empty() && !duplicate.Icon.empty() && software.Icon != duplicate.Icon)
			{
				swList->push_back(software);
				return;
			}

			if (software.Icon.empty())
			{
				software.Icon = duplicate.Icon;
			}

			// Merge Location
			if (!software.InstallLocation.empty()
				&& !duplicate.InstallLocation.empty()
				&& software.InstallLocation != duplicate.InstallLocation)
			{
				swList->push_back(software);
				return;
			}

			if (software.InstallLocation.empty())
			{
				software.InstallLocation = duplicate.InstallLocation;
			}

			// Merge Version
			if (!software.Version.empty() && !duplicate.Version.empty() && software.Version != duplicate.Version)
			{
				swList->push_back(software);
				return;
			}

			if (software.Version.empty())
			{
				software.Version = duplicate.Version;
			}

			swList->erase(swList->begin() + index);
			swList->push_back(software);
		}
	}

	static wstring reverseString(wstring input);

	static void replaceAll(wstring& str, const wstring& from, const wstring& to);

	static vector<wstring> split(const wstring& text, wchar_t delimiter);

	static wstring getInstallerKeyNameFromGuid(wstring guidName)
	{
		replaceAll(guidName, L"{", L"");
		replaceAll(guidName, L"}", L"");
		const vector<wstring> msiNameParts = split(guidName, L'-');
		wstring msiName;

		// Just reverse the first 3 parts
		for (int i = 0; i <= 2; i++)
		{
			msiName.append(reverseString(msiNameParts[i]));
		}

		// For the last 2 parts, reverse each character pair
		for (int j = 3; j <= 4; j++)
		{
			for (int i = 0; i <= static_cast<int>(msiNameParts[j].length()) - 1; i++)
			{
				msiName.append(wstring(1, msiNameParts[j].c_str()[i + 1]));
				msiName.append(wstring(1, msiNameParts[j].c_str()[i]));
				i += 1;
			}
		}

		return msiName;
	}

	static wstring reverseString(wstring input)
	{
		std::reverse(input.begin(), input.end());
		return input;
	}

	static void replaceAll(wstring& str, const wstring& from, const wstring& to)
	{
		if (from.empty())
		{
			return;
		}

		size_t startPos = 0;
		while ((startPos = str.find(from, startPos)) != wstring::npos)
		{
			str.replace(startPos, from.length(), to);
			startPos += to.length();
		}
	}

	static vector<wstring> split(const wstring& text, const wchar_t delimiter)
	{
		vector<wstring> result;
		wstring::size_type start = 0;
		wstring::size_type end = text.find(delimiter, start);

		while (end != wstring::npos)
		{
			wstring token = text.substr(start, end - start);
			result.push_back(token);
			start = end + 1;
			end = text.find(delimiter, start);
		}

		result.push_back(text.substr(start));

		return result;
	}
}
