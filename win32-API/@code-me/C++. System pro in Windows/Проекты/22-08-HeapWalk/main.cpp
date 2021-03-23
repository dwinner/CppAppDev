#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hHeap;
  int  size = 4096;            // размер кучи
  int  *a = NULL, *b = NULL;   // указатели на массивы
  PROCESS_HEAP_ENTRY  phe;     // состояние элемента кучи

  // создаем кучу динамически
  hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, 0);
  // распределям память под массивы
  a = (int*)HeapAlloc(hHeap, NULL, 4 * sizeof(int));
  b = (int*)HeapAlloc(hHeap, NULL, 16 * sizeof(int));
  // инициализируем цикл проверки состояния кучи
  phe.lpData = NULL;
  // проверяем состояние элементов кучи
  while (HeapWalk(hHeap, &phe));
  {
    if (phe.wFlags & PROCESS_HEAP_REGION)
      cout << "PROCESS_HEAP_REGION flag is set." << endl;
    if (phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE)
      cout << "PROCESS_HEAP_UNCOMMITTED_RANGE flag is set" << endl;
    cout << "lpData = " << phe.lpData << endl;
    cout << "cbData = " << phe.cbData << endl;
    cout << endl;
  }  
  // разрушаем кучу
  HeapDestroy(hHeap);

  return 0;
}