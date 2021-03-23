#include <windows.h>
#include <iostream.h>

HANDLE  hHeap;

DWORD WINAPI thread(LPVOID)
{
  int  *a;
  // бесконечный цикл распределения и освобождения памяти из кучи
  for ( ; ; )
  {
    // распределяем память
    a = (int*)HeapAlloc(hHeap, NULL, sizeof(int));
    cout << "\tHeap allocated." << endl;
    // освобождаем память
    HeapFree(hHeap, NULL, a);
    cout << "\tHeap freed." << endl;
    // немного подождем
    Sleep(2000);
  }
}

int main()
{
  HANDLE   hThread;
  DWORD  IDThread;
  int  size = 4096;  // размер кучи
  char c;            // служебный символ

  // создаем кучу динамически
  hHeap = HeapCreate(NULL, size, 0);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
  // напечатаем как управлять программой
  cout << "Input " << endl;
  cout << "\tl - to lock the heap." << endl;
  cout << "\tu - to unlock the heap." << endl;
  cout << "\te - to exit from the process." << endl << endl;
  // ждем ввод символа для продолжения выполнения программы
  cout << "Now input any char to continue: ";
  cin >> c;
  // запускаем поток, работающий с кучей
  hThread = CreateThread(NULL, 0, thread, NULL, NULL, &IDThread);
  if (!hThread)
  {
    cout << "Create thread failed." << endl;
    return GetLastError();
  }
  // блокируем/разблокируем кучу
  for ( ; ; )
  {    
    cin >> c;
    switch (c)
    {
    case 'l':
      if (!HeapLock(hHeap))
      {
        cout << "Heap lock failed." << endl;
        return GetLastError();
      }
      cout << "Heap locked." << endl;
      break;

    case 'u':
      if (!HeapUnlock(hHeap))
      {
        cout << "Heap unlock failed." << endl;
        return GetLastError();
      }
      cout << "Heap unlocked." << endl;
      break;

    case 'e':
      // разрушаем кучу
      if (!HeapDestroy(hHeap))
      {
        cout << "Heap destroy failed." << endl;
        return GetLastError();
      }
      // прерываем выполнение потока thread
      TerminateThread(hThread, 0);
      // закрываем дескриптор потока
      CloseHandle(hThread);
      // выводим сообщение о завершении работы
      cout << "Exit from the process." << endl;

      return 0;
    }
  }
}