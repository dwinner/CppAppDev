#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int  *a = NULL;    // указатель на массив
  int  *b = NULL;    // указатель на массив
  int  *c = NULL;    // указатель на массив
  int  size = 4096;  // размер кучи
  UINT free;         // длина свободной памяти после уплотнения

  // создаем кучу динамически
  hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, size);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
    // распределям память под массивы
  a = (int*)HeapAlloc(hHeap, NULL, 1024);
  cout << "a = " << a << endl;
  b = (int*)HeapAlloc(hHeap, NULL, 1024);
  cout << "b = " << b << endl;
  c = (int*)HeapAlloc(hHeap, NULL, 1024);
  cout << "c = " << c << endl << endl;

  // проверяем, сколько осталось свободного места в куче
  free = HeapCompact(hHeap, HEAP_NO_SERIALIZE);
  if (!free) 
  {
    cout << "Heap compact failed." << endl;
    return GetLastError();
  }
  else
    cout << "Free: " << free << endl;

  // освобождаем первых два массива
  HeapFree(hHeap, NULL, b);
  HeapFree(hHeap, NULL, a);

  // уплотняем кучу
  free = HeapCompact(hHeap, HEAP_NO_SERIALIZE);
  if (!free) 
  {
    cout << "Heap compact failed." << endl;
    return GetLastError();
  }
  else
    cout << "Free: " << free << endl;

  // разрушаем кучу
  HeapDestroy(hHeap);

  return 0;
}