#include <windows.h>
#include <iostream.h>

DWORD  dwTlsIndex;   // индекс динамической локальной памяти потока

// главная функция
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
  BOOL  retVal = TRUE;   // возвращаемое значение
  int    *pCount;        // указатель на счетчик

  switch (dwReason)
  {
  case DLL_PROCESS_ATTACH:   // загрузка DLL
    // распределяем локальную память потоков
    dwTlsIndex = TlsAlloc();
    if (dwTlsIndex == -1)
    {
      cerr << "Tls allocation failed." << endl;
      retVal = FALSE;
    }
    break;
  case DLL_THREAD_ATTACH:    // создание потока
    // захватываем память под счетчик
    pCount = new int(0);
    // запоминаем указатель в индексе
    if (!TlsSetValue(dwTlsIndex, (LPVOID)pCount))
    {
      cerr << "Tls set value failed." << endl;
      retVal = FALSE;
    }
    break;
  case DLL_THREAD_DETACH:    // завершение потока
    // получаем указатель из индекса
    pCount = (int*)TlsGetValue(dwTlsIndex);
    // если ошибка, то выдаем сообщение
    if (!pCount)
    {
      cerr << "Tls get value failed." << endl;
      retVal = FALSE;
    }
    // иначе, освобождаем память
    else
      delete pCount;
    break;
  case DLL_PROCESS_DETACH:  // отключение DLL
    // освобождаем локальную память потока
    if (!TlsFree(dwTlsIndex))
    {
      cerr << "Tls free failed." << endl;
      retVal = FALSE;
    }
    break;
  }

  return retVal;
}

extern "C" __declspec(dllexport) int Add(int n)
{
  int  *pCount;

  // получаем указатель на локальный счетчик
  pCount = (int*)TlsGetValue(dwTlsIndex);
  if (!pCount)
  {
    cerr << "Tls get value failed." << endl;
    return GetLastError();
  }
  // увеличиваем значение счетчика
  *pCount += n;

  return *pCount;
}