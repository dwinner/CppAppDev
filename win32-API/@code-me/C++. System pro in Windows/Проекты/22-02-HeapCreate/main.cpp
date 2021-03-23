#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int  *a = NULL;        // указатель на массив
  int  h_size = 4096;    // размер кучи
  int  a_size = 2048;    // размер массива 

  // создаем кучу динамически
  hHeap = HeapCreate(HEAP_NO_SERIALIZE, h_size, h_size);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
  // распределям память под массив
  a = (int*)HeapAlloc(hHeap, NULL, a_size);
  // обрабатываем ошибку в случае неудачи
  if (!a)
  {
    cout << "Heap allocation failed." << endl;
    return GetLastError();
  }
  // распечатываем распределённую память
  cout << "a[10] = " << a[10] << endl;
  // освобождаем память из кучи
  if (!HeapFree(hHeap, NULL, a))
  {
    cout << "Heap free failed." << endl;
    return GetLastError();
  }
  // разрушаем кучу
  if (!HeapDestroy(hHeap))
  {
    cout << "Heap destroy failed." << endl;
    return GetLastError();
  }

  return 0;
}