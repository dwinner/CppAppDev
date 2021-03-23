#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int *a = NULL;     // указатель на массив
  int size = 1000;   // размерность массива

  // получаем дескриптор кучи процесса, созданной по умолчанию
  hHeap = GetProcessHeap();
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
  // распределяем память под массив
  a = (int*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, size * sizeof(int));
  // распечатываем один элемент массива
  cout << "a[10] = " << a[10] << endl;
  // освобождаем память из кучи
  if (!HeapFree(hHeap, NULL, a))
  {
    cout << "Heap free failed." << endl;
    return GetLastError();
  }

  return 0;
}