#include <windows.h>

__declspec(thread) int count = 0;

// ������� �������
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
  switch (dwReason)
  {
  case DLL_PROCESS_ATTACH:   // �������� DLL 
    break;
  case DLL_THREAD_ATTACH:    // �������� ������
    break;
  case DLL_THREAD_DETACH:    // ���������� ������
    break;
  case DLL_PROCESS_DETACH:   // ���������� DLL
    break;
  }

  return TRUE;
}

extern "C" __declspec(dllexport) int Add(int n)
{
  count += n;

  return count;
}