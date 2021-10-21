#ifndef INSTALLED_PROGRAMS
#define INSTALLED_PROGRAMS
#include <vector>
#include <Windows.h>
#include "RegistryKey.h"

namespace programList
{
	class SoftwareEntity
	{
	public:
		std::wstring DisplayName;

		std::wstring InstallLocation;

		std::wstring Version;

		Arch Architecture; // 32 or 64

		std::wstring Icon;

		SoftwareEntity(std::wstring, std::wstring, std::wstring, std::wstring, Arch);
	};

	class InstalledPrograms
	{
	public:
		InstalledPrograms();

		~InstalledPrograms();

		static std::vector<SoftwareEntity>* GetInstalledPrograms(bool includeUpdates);

	private:
		static std::vector<SoftwareEntity>* GetInstalledProgramsImp(bool includeUpdates);

		static std::vector<SoftwareEntity>* GetUninstallKeyPrograms(RegistryKey* uninstallKey, RegistryKey* classesKey,
		                                                            std::vector<SoftwareEntity>*, bool includeUpdates);

		static std::vector<SoftwareEntity>* GetUserInstallerKeyPrograms(RegistryKey* uInstallerKey,
		                                                                std::vector<SoftwareEntity>*
		                                                                existingProgramList);
	};
}

#endif
