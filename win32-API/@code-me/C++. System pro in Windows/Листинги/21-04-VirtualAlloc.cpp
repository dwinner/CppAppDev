#include <windows.h>
#include <iostream.h>

int main()
{
  int *a;    // указатель на массив целых чисел
  const int size = 1024;   // размерность массива

  // распределяем виртуальную память
  a = (int*)VirtualAlloc(
      NULL, 
      size * sizeof(int), 
      MEM_COMMIT, 
      PAGE_READWRITE|PAGE_GUARD);
  if(!a)
  {
    cout << "Virtual allocation failed." << endl;
    return GetLastError();
  }

  __try
  {
    a[10] = 10;
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    DWORD ecode = GetExceptionCode();

    if (ecode == EXCEPTION_GUARD_PAGE)
      cout << "Access to a guard virtual page." << endl;
    else
      cout << "Some exception." << endl;
  }

  cout << "a[10] = " << a[10] << endl;
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