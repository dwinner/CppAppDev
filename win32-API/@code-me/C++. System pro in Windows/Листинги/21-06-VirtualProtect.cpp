#include <windows.h>
#include <iostream.h>

int main()
{
  DWORD  dwOldProtect;     // для старых атрибутов защиты  
  int *a;                  // указатель на массив целых чисел
  const int size = 1000;   // размерность массива

  // распределяем виртуальную память
  a = (int*)VirtualAlloc(
      NULL, 
      size * sizeof(int), 
      MEM_COMMIT, 
      PAGE_READONLY);
  if(!a)
  {
    cout << "Virtual allocation failed." << endl;
    return GetLastError();
  }

  // попробуем записать в виртуальную память
  __try
  {
    a[10] = 10;
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    DWORD ecode = GetExceptionCode();

    if (ecode == EXCEPTION_ACCESS_VIOLATION)
      cout << "Access to write protected page." << endl;
    else
      cout << "Some exception." << endl;
  }

  // изменим атрибуты доступа
  if (!VirtualProtect(a, size, PAGE_READWRITE, &dwOldProtect))
  {
    cout << "Virtual protect failed." << endl;
    return GetLastError();
  }

  // теперь можно писать в виртуальную память 
  a[10] = 10;
  cout << "a[10] = " << a[10] << endl;

  // освобождаем виртуальную память
  if (!VirtualFree(a, 0, MEM_RELEASE))
  {
    cout << "Memory release failed." << endl;
    return GetLastError();
  }

  return 0;
}