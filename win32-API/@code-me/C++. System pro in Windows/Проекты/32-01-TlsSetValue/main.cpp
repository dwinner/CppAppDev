#include <windows.h>
#include <iostream.h>

DWORD thread(void)
{
  char  c;
  DWORD  dwFirstTlsIndex, dwPrevTlsIndex, dwNextTlsIndex;

  // распределяем первый tls индекс
  dwFirstTlsIndex = TlsAlloc();
  if (dwFirstTlsIndex == -1)
  {
    cerr << "Tls allocation failed." << endl;
    return GetLastError();
  }
  // устанавливаем предыдущий tls индекс равным первому индексу
  dwPrevTlsIndex = dwFirstTlsIndex;
  // двигаемся дальше по tls индексам
  for (;;)
  {
    // выводим на экран предыдущий tls индекс
    cout << "Alloc tls index = " << dwPrevTlsIndex << endl;
    Sleep(50);
    // распределяем следующий tls индекс
    dwNextTlsIndex = TlsAlloc();
    // если больше индексов нет, то выходим из цикла
    if (dwNextTlsIndex == -1)
      break;
    // запомним следующий tls индекс в предыдущем индексе
    if (!TlsSetValue(dwPrevTlsIndex, (LPVOID)dwNextTlsIndex))
    {
      cerr << "Tls set value failed." << endl;
      return GetLastError();
    }
    // продвигаем индексы
    dwPrevTlsIndex = dwNextTlsIndex;
  }

  // ждем команду на освобождение индексов
  cout << "Input any char to free tls indexes: ";
  cin >> c;

  // устанавливаем предыдущий tls индекс в первый
  dwPrevTlsIndex = dwFirstTlsIndex;
    // двигаемся дальше по tls индексам
  for (;;)
  {
    // выводим на экран предыдущий tls индекс 
    cout << "Free tls index = " << dwPrevTlsIndex << endl;
    Sleep(50);
    // получаем следующий tls индекс
    dwNextTlsIndex = (DWORD)TlsGetValue(dwPrevTlsIndex);
    if (!dwNextTlsIndex)
      break;
    // освобождаем предыдущий tls индекс
    if (!TlsFree(dwPrevTlsIndex))
    {
      cerr << "Tls free failed." << endl;
      return GetLastError();
    }
    // продвигаем индексы
    dwPrevTlsIndex = dwNextTlsIndex;
  }

  // ждем команду на выход из потока
  cout << "Input any char to exit: ";
  cin >> c;

  return 0;
}

int main()
{
  HANDLE  hThread;
  DWORD  IDThread;

  // запускаем поток
  hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, 
               NULL, 0, &IDThread);
  if (hThread == NULL)
  {
    cerr << "Create thread failed." << endl;
    return GetLastError();
  }
  // ждем, пока поток Add закончит работу
  WaitForSingleObject(hThread, INFINITE);
  // закрываем дескриптор потока
  CloseHandle(hThread);

  return 0;
}