#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int  *a = NULL;      // указатель на массив
  int  size = 4096;    // размер массива, а также кучи

  // создаем кучу динамически
  hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, size);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
  // пытаемся распределить память под массив
  a = (int*)HeapAlloc(hHeap, NULL, size * sizeof(int));
  // обрабатываем ошибку в случае неудачи
  if (!a)
  {
    cout << "Heap allocation failed." << endl;
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