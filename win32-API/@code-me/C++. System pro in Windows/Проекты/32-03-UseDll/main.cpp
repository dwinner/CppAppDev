#include <windows.h>
#include <iostream.h>

int (*Add)(int);   // указатель на функцию Add из DLL

DWORD WINAPI thread(LPVOID iNum)
{
  for (int i = 0; i < (int)iNum; ++i)
  {
    cout << "count = " << Add((int)iNum) << endl;
    Sleep(15);
  }

  return 0;
}

int main()
{
  char  c;
  HMODULE  hDll;       // дескриптор DLL
  HANDLE  hThread[2];  // дескрипторы потоков
  DWORD  IDThread[2];  // идентификаторы потоков

  // загружаем динамически подключаемую библиотеку
  hDll = LoadLibrary("Count.dll");
  if (!hDll)
  {
    cerr << "Load library failed." << endl;
    return GetLastError();
  }
  // настраиваем адрес функци
  Add = (int (*)(int))GetProcAddress(hDll, "Add");
  if (!Add)
  {
    cerr << "Get procedure address failed." << endl;
    return GetLastError();
  }
  // запускаем потоки
  hThread[0] = CreateThread(NULL, 0, thread, (void*)3, 0, &IDThread[0]);
  hThread[1] = CreateThread(NULL, 0, thread, (void*)5, 0, &IDThread[1]);
  if (hThread[0] == NULL || hThread[1] == NULL)
  {
    cerr << "Create thread failed." << endl;
    return GetLastError();
  }
  // ждем завершения потоков
  WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
  // отключаем библиотеку
  if (!FreeLibrary(hDll))
  {
    cerr << "Free library failed." << endl;
    return GetLastError();
  }
  // выходим из программы
  cout << "Input any char to exit: ";
  cin >> c;

  return 0;
}