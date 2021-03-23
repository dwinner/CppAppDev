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

extern "C" int count = -5;

extern "C" int Add(int n)
{
  count += n;

  return count;
}

extern "C" int Sub(int n)
{
  count -= n;

  return count;
}