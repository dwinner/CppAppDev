#include <windows.h>
#include <iostream.h>

volatile UINT  nCount;
volatile DWORD dwCount;

void thread()
{
  for (;;)
  {
    nCount++;
    // ���������������� ����� �� 100 �����������
    Sleep(100);
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
    cout << "Input :" << endl;
    cout << "\t'n' to exit" << endl;
    cout << "\t'y' to display the count" << endl;
    cout << "\t's' to suspend thread" << endl;
    cout << "\t'r' to resume thread" << endl;
    cin >> c;

    if (c == 'n')
      break;
    switch (c)
    {
    case 'y':
      cout << "count = " << nCount << endl;
      break;
    case 's':
      // ���������������� ����� thread
      dwCount = SuspendThread(hThread);
      cout << "Thread suspend count = " << dwCount << endl;
      break;
    case 'r':
      // ������������ ����� thread
      dwCount = ResumeThread(hThread);
      cout << "Thread suspend count = " << dwCount << endl;
      break;
    }
  }
  
  // ��������� ���������� ������ thread
  TerminateThread(hThread, 0);
  // ��������� ���������� ������ thread
  CloseHandle(hThread);

  return 0;
}