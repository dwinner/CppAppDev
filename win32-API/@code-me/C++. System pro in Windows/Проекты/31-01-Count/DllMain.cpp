#include <windows.h>

// главная функция
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
  switch (dwReason)
  {
  case DLL_PROCESS_ATTACH:   // загрузка DLL 
    break;
  case DLL_THREAD_ATTACH:    // создание потока
    break;
  case DLL_THREAD_DETACH:    // завершение потока
    break;
  case DLL_PROCESS_DETACH:   // отключение DLL
    break;
  }

  return TRUE;
}

extern "C" __declspec(dllexport) int count = 0;

extern "C" __declspec(dllexport) int Add(int n)
{
  count += n;

  return count;
}

extern "C" __declspec(dllexport) int Sub(int n)
{
  count -= n;

  return count;
}