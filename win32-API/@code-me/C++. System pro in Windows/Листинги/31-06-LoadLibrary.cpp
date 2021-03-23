#include <windows.h>
#include <iostream.h>

int main()
{
  HMODULE  hDll;     // дескриптор DLL
  int (*Add)(int);   // указатель на функцию Add из DLL
  int (*Sub)(int);   // указатель на функцию Sub из DLL
  int *pCount;       // указатель на переменную count из DLL

  // загружаем динамически подключаемую библиотеку
  hDll = LoadLibrary("Count.dll");
  if (!hDll)
  {
    cerr << "Load library failed." << endl;
    return GetLastError();
  }
  // настраиваем адрес переменной count из DLL
  pCount = (int *)GetProcAddress(hDll, MAKEINTRESOURCE(1));
  if (!pCount)
  {
    cerr << "Get variable address failed." << endl;
    return GetLastError();
  }
  // выводим начальное значение переменной count
  cout << "Initial count = " << (*pCount) << endl;
  // настраиваем адреса функций
  Add = (int (*)(int))GetProcAddress(hDll, MAKEINTRESOURCE(2));
  Sub = (int (*)(int))GetProcAddress(hDll, MAKEINTRESOURCE(3));
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