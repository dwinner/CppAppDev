#include <windows.h>
#include <iostream.h>

HANDLE  hHeap;

DWORD WINAPI thread(LPVOID)
{
  int  *a;
  // ����������� ���� ������������� � ������������ ������ �� ����
  for ( ; ; )
  {
    // ������������ ������
    a = (int*)HeapAlloc(hHeap, NULL, sizeof(int));
    cout << "\tHeap allocated." << endl;
    // ����������� ������
    HeapFree(hHeap, NULL, a);
    cout << "\tHeap freed." << endl;
    // ������� ��������
    Sleep(2000);
  }
}

int main()
{
  HANDLE   hThread;
  DWORD  IDThread;
  int  size = 4096;  // ������ ����
  char c;            // ��������� ������

  // ������� ���� �����������
  hHeap = HeapCreate(NULL, size, 0);
  if (!hHeap)
  {
    cout << "Heap create failed." << endl;
    return GetLastError();
  }
  // ���������� ��� ��������� ����������
  cout << "Input " << endl;
  cout << "\tl - to lock the heap." << endl;
  cout << "\tu - to unlock the heap." << endl;
  cout << "\te - to exit from the process." << endl << endl;
  // ���� ���� ������� ��� ����������� ���������� ���������
  cout << "Now input any char to continue: ";
  cin >> c;
  // ��������� �����, ���������� � �����
  hThread = CreateThread(NULL, 0, thread, NULL, NULL, &IDThread);
  if (!hThread)
  {
    cout << "Create thread failed." << endl;
    return GetLastError();
  }
  // ���������/������������ ����
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
      // ��������� ����
      if (!HeapDestroy(hHeap))
      {
        cout << "Heap destroy failed." << endl;
        return GetLastError();
      }
      // ��������� ���������� ������ thread
      TerminateThread(hThread, 0);
      // ��������� ���������� ������
      CloseHandle(hThread);
      // ������� ��������� � ���������� ������
      cout << "Exit from the process." << endl;

      return 0;
    }
  }
}