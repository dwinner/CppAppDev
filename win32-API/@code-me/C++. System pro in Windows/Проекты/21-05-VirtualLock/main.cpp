#include <windows.h>
#include <iostream.h>

int main()
{
  LPVOID  vm;  // указатель на виртуальную память
  SIZE_T  size = 4096;   // размер памяти

  // распределяем виртуальную память
  vm = VirtualAlloc(
      NULL, 
      size, 
      MEM_COMMIT, 
      PAGE_READWRITE);
  if(!vm)
  {
    cout << "Virtual allocation failed." << endl;
    return GetLastError();
  }

  // блокируем виртуальную память
  if (!VirtualLock(vm, size))
  {
    cout << "Virtual lock failed." << endl;
    return GetLastError();
  }
  // разблокируем виртуальную память
  if (!VirtualUnlock(vm, size))
  {
    cout << "Virtual unlock failed." << endl;
    return GetLastError();
  }
  
  // освобождаем виртуальную память
  if (!VirtualFree(vm, 0, MEM_RELEASE))
  {
    cout << "Memory release failed." << endl;
    return GetLastError();
  }

  return 0;
}