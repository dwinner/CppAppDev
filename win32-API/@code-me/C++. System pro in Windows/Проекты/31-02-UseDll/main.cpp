#include <windows.h>
#include <iostream.h>

int main()
{
  HMODULE  hDll;     // дескриптор DLL
  int (*Add)(int);   // для адреса функции Add из DLL
  int (*Sub)(int);   // для адреса функции Sub из DLL
  int *pCount;       // для адреса переменной count из DLL

  // загружаем динамически подключаемую библиотеку
  hDll = LoadLibrary("Count.dll");
  if (!hDll)
  {
    cerr << "Load library failed." << endl;
    return GetLastError();
  }
  // настраиваем адрес переменной count из DLL
  pCount = (int *)GetProcAddress(hDll, "count");
  if (!pCount)
  {
    cerr << "Get variable address failed." << endl;
    return GetLastError();
  }
  // выводим начальное значение переменной count
  cout << "Initial count = " << (*pCount) << endl;
  // настраиваем адреса функций
  Add = (int (*)(int))GetProcAddress(hDll, "Add");
  Sub = (int (*)(int))GetProcAddress(hDll, "Sub");
  if (!Add || !Sub)
  {
    cerr << "Get procedure address failed." << endl;
    return GetLastError();
  }
  // изменяем значение счетчика
  cout << "count = " << Add(20) << endl;
  cout << "count = " << Sub(15) << endl;
  // отключаем библиотеку
  if (!FreeLibrary(hDll))
  {
    cerr << "Free library failed." << endl;
    return GetLastError();
  }
  // выходим из программы
  cout << "Press any key to exit.";
  cin.get();

  return 0;
}