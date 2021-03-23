#include <windows.h>
#include <iostream.h>

extern "C" __declspec(dllimport) int Add(int n);

DWORD WINAPI thread(LPVOID iNum)
{
  cout << "count from thread = " << Add((int)iNum) << endl;

  return 0;
}

int main()
{
  HANDLE  hThread;     // дескрипторы потоков
  DWORD  IDThread;     // идентификаторы потоков

  // изменяем значение счетчика
  cout << "count from main = " << Add(20) << endl;

  // запускаем поток
  hThread = CreateThread(NULL, 0, thread, (void*)10, 0, &IDThread);
  if (hThread == NULL)
  {
    cerr << "Create thread failed." << endl;
    return GetLastError();
  }
  // ждем завершения потока
  WaitForSingleObject(hThread, INFINITE);
  // выходим из программы
  cout << "Press any key to exit.";
  cin.get();

  return 0;
}