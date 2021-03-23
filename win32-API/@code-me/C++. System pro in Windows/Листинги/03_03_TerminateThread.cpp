#include <windows.h>
#include <iostream.h>

volatile UINT count;

void thread()
{
  for (;;)
  {
    ++count;
    Sleep(100);    // ������� ��������
  }
}

int main()
{
  HANDLE   hThread;
  DWORD  IDThread;
  char c;

  hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 
                         0, &IDThread);
  if (hThread == NULL)
    return GetLastError();

  for (;;)
  {
    cout << "Input 'y' to display the count or any char to finish: ";
    cin >> c;
    if (c == 'y')
      cout << "count = " << count << endl;
    else
      break;
  }
  
  // ��������� ���������� ������ thread
  TerminateThread(hThread, 0);

  // ��������� ���������� ������
  CloseHandle(hThread);

  return 0;
}