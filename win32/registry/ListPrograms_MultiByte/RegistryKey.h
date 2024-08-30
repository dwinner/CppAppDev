#ifndef REGISTRY_KEY
#define REGISTRY_KEY

#include <Windows.h>
#include <string>
#include <vector>

namespace programList
{
	enum Arch
	{
		UnKnown = 0,
		X86 = 1,
		X64 = 2
	};

	class RegistryKey
	{
	public:
		~RegistryKey();

		RegistryKey* OpenSubKey64(const std::string& subKey) const;

		RegistryKey* OpenSubKey32(const std::string& subKey) const;

		RegistryKey* OpenSubKey(const std::string& subKey) const;

		RegistryKey* OpenSubKey(const std::string& subKey, Arch arch) const;

		std::vector<std::string> GetSubKeyNames() const;

		std::string GetValue(const std::string& query) const;

		static RegistryKey& GetHklmKey();

		static RegistryKey& GetHkuKey();

		Arch KeyArch; // Indicate whether the Key is a 64 bit or 32 bit Key.

	private:
		HKEY hkey_;
		RegistryKey(HKEY, Arch); // The constructor is private, not explicit initilization is available.
	};
}

#endif
