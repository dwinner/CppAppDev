#include "RegistryKey.h"

namespace programList
{
	using namespace std;

	RegistryKey::RegistryKey(HKEY hkey, Arch arch)
	{
		this->hkey_ = hkey;
		this->KeyArch = arch;
	}

	RegistryKey::~RegistryKey(void)
	{
		if (this->hkey_ == HKEY_LOCAL_MACHINE || this->hkey_ == HKEY_USERS)
		{
			return;
		}

		RegCloseKey(this->hkey_);
	}

	RegistryKey* RegistryKey::OpenSubKey64(const wstring& subKey) const
	{
		HKEY hKey;
		return RegOpenKeyEx(this->hkey_, subKey.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS
			       ? nullptr
			       : new RegistryKey(hKey, X64);
	}

	RegistryKey* RegistryKey::OpenSubKey32(const wstring& subKey) const
	{
		HKEY hKey;
		return RegOpenKeyEx(this->hkey_, subKey.c_str(), 0, KEY_READ | KEY_WOW64_32KEY, &hKey) != ERROR_SUCCESS
			       ? nullptr
			       : new RegistryKey(hKey, X86);
	}

	RegistryKey* RegistryKey::OpenSubKey(const wstring& subKey) const
	{
		HKEY hKey;
		return RegOpenKeyEx(this->hkey_, subKey.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS
			       ? nullptr
			       : new RegistryKey(hKey, UnKnown);
	}

	RegistryKey* RegistryKey::OpenSubKey(const wstring& subKey, const Arch arch) const
	{
		HKEY hKey;
		const DWORD flag = arch != X64
			                   ? arch == X86
				                     ? KEY_WOW64_32KEY
				                     : 0
			                   : KEY_WOW64_64KEY;
		return RegOpenKeyEx(this->hkey_, subKey.c_str(), 0, KEY_READ | flag, &hKey) != ERROR_SUCCESS
			       ? nullptr
			       : new RegistryKey(hKey, arch);
	}

	RegistryKey& RegistryKey::GetHklmKey()
	{
		static RegistryKey registryKey(HKEY_LOCAL_MACHINE, UnKnown); // NOLINT(clang-diagnostic-exit-time-destructors)
		return registryKey;
	}

	RegistryKey& RegistryKey::GetHkuKey()
	{
		static RegistryKey registryKey(HKEY_USERS, UnKnown); // NOLINT(clang-diagnostic-exit-time-destructors)
		return registryKey;
	}

	vector<wstring> RegistryKey::GetSubKeyNames() const
	{
		vector<wstring> subKeyNames;
		LONG lRet;
		DWORD dwIndex = 0;
		DWORD cbName = MAX_PATH;
		WCHAR szSubKeyName[MAX_PATH];

		while ((lRet = RegEnumKeyEx(this->hkey_,
		                            dwIndex,
		                            szSubKeyName,
		                            &cbName,
		                            nullptr,
		                            nullptr,
		                            nullptr,
		                            nullptr)) != ERROR_NO_MORE_ITEMS)
		{
			if (lRet == ERROR_SUCCESS)
			{
				subKeyNames.emplace_back(szSubKeyName);
			}

			cbName = MAX_PATH;
			dwIndex++;
		}

		return subKeyNames;
	}

	wstring RegistryKey::GetValue(const wstring& query) const
	{
		WCHAR value[MAX_PATH];
		DWORD dwSize = sizeof value;
		DWORD dwType;

		if (RegQueryValueEx(this->hkey_,
		                    query.c_str(),
		                    nullptr,
		                    &dwType,
		                    reinterpret_cast<LPBYTE>(&value),
		                    &dwSize) != ERROR_SUCCESS)
		{
			return L"";
		}

		if (dwType == REG_DWORD)
		{
			const DWORD* pEncodedValue = reinterpret_cast<DWORD*>(value);
			const int encodedValue = static_cast<int>(*pEncodedValue);
			const errno_t errorCode = _itow_s(encodedValue, value, MAX_PATH, 10);
			return wstring(errorCode == 0 ? value : L"");
		}

		if (dwType == REG_SZ)
		{
			return wstring(value);
		}

		if (dwType == REG_EXPAND_SZ)
		{
			WCHAR expanded[MAX_PATH];
			ExpandEnvironmentStrings(value, expanded, MAX_PATH);
			return wstring(expanded);
		}

		return L"";
	}
}
