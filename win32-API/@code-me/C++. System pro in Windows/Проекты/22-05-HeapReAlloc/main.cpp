#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int  *a = NULL;        // указатель на массив
  int  h_size = 4096;    // размер кучи
  int  a_size = 5;       // размер массива

  // создаем кучу динамически
  hHeap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_GENERATE_EXCEPTIONS,
    h_size, 0);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
  // распределяем память из кучи
  a = (int*)HeapAlloc(hHeap, NULL, a_size * sizeof(int));
  // инициализируем и распечатываем массив
  for (int i = 0; i < a_size; i++)
  {
    a[i] = i;
    cout << "a[" << i << "] = " << a[i] << endl;
  }
  // распределяем дополнительный блок
  a = (int*)HeapReAlloc(hHeap, HEAP_ZERO_MEMORY, a, 
                 2 * a_size * sizeof(int));
  // распечатываем элементы массива
  for (i = 0; i < 2 * a_size; i++)
    cout << "\ta[" << i << "] = " << a[i] << endl;
  // разрушаем кучу
  if (!HeapDestroy(hHeap))
  {
    cout << "Heap destroy failed." << endl;
    return GetLastError();
  }

  return 0;
}