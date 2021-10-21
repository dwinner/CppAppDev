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
		~RegistryKey(void);

		RegistryKey* OpenSubKey64(const std::wstring& subKey) const;

		RegistryKey* OpenSubKey32(const std::wstring& subKey) const;

		RegistryKey* OpenSubKey(const std::wstring& subKey) const;

		RegistryKey* OpenSubKey(const std::wstring& subKey, Arch arch) const;

		std::vector<std::wstring> GetSubKeyNames() const;

		std::wstring GetValue(const std::wstring& query) const;

		static RegistryKey& GetHklmKey();

		static RegistryKey& GetHkuKey();

		Arch KeyArch; // Indicate whether the Key is a 64 bit or 32 bit Key.

	private:
		HKEY hkey_;
		RegistryKey(HKEY, Arch); // The constructor is private, not explicit initilization is available.
	};
}

#endif
