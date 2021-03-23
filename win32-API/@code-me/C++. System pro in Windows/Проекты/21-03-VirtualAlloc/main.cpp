#include <windows.h>
#include <iostream.h>

int main()
{
  LPVOID  lpr, lpc;
  const int Kb = 1024;
  const int size = 100;

  // резервируем виртуальную память
  lpr = VirtualAlloc(
      (LPVOID) 0x00880000, 
      size * Kb, 
      MEM_RESERVE, 
      PAGE_READWRITE);
  if(!lpr)
  {
    cout << "Virtual memory reservation failed." << endl;
    return GetLastError();
  }

  cout << "Virtual memory address: " << lpr << endl;

  // распределяем виртуальную память
  lpc = VirtualAlloc(
      (LPVOID) 0x00888000, 
      Kb, 
      MEM_COMMIT, 
      PAGE_READWRITE);
  if(!lpc)
  {
    cout << "Virtual memory allocation failed." << endl;
    return GetLastError();
  }

  cout << "Virtual memory address: " << lpc << endl;

  // отменяем распределение
  if (!VirtualFree(lpc, Kb, MEM_DECOMMIT))
  {
    cout << "Memory decommit failed." << endl;
    return GetLastError();
  }

  // освобождаем виртуальную память
  if (!VirtualFree(lpr, 0, MEM_RELEASE))
  {
    cout << "Memory release failed." << endl;
    return GetLastError();
  }

  return 0;
}