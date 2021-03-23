#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int  *a = NULL;    // указатель на массив
  int  size = 4096;  // размер кучи

  // создаем кучу динамически
  hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, 0);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
  // распределяем память под массивы
  a = (int*)HeapAlloc(hHeap, NULL, 4 * sizeof(int));
  // проверяем состояние распределенного блока памяти
  if (!HeapValidate(hHeap, HEAP_NO_SERIALIZE, a))
    cout << "The block is bad." << endl;
  else
    cout << "The block is good." << endl;

  // разрушаем кучу
  HeapDestroy(hHeap);

  return 0;
}