#include <windows.h>
#include <iostream.h>

int main()
{
  int *a;    // указатель на массив целых чисел
  const int size = 1000;   // размерность массива

  // распределяем виртуальную память
  a = (int*)VirtualAlloc(
      NULL, 
      size * sizeof(int), 
      MEM_COMMIT, 
      PAGE_READWRITE);
  if(!a)
  {
    cout << "Virtual allocation failed." << endl;
    return GetLastError();
  }

  cout << "Virtual memory address: " << a << endl;

  // освобождаем виртуальную память
  if (!VirtualFree(a, 0, MEM_RELEASE))
  {
    cout << "Memory release failed." << endl;
    return GetLastError();
  }

  return 0;
}