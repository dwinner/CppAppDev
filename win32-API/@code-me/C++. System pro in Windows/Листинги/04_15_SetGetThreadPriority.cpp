#include <windows.h>
#include <conio.h>

int main()
{
  HANDLE  hThread;
  DWORD  dwPriority;

  // �������� ���������������� �������� ������
  hThread = GetCurrentThread();
  
  // ������ ������� ���������� �������� ��������
  dwPriority = GetThreadPriority(hThread);
  _cprintf("The priority level of the thread = %d.\n", dwPriority);

  // �������� ��������� �������� ������
  if (!SetThreadPriority(hThread, THREAD_PRIORITY_LOWEST))
  {
    _cputs("Set thread priority failed.\n");
    _cputs("Press any key to exit.\n");
    _getch();
    return GetLastError();
  }
  // ������ ������� ��������� �������� ������
  dwPriority = GetThreadPriority(hThread);
  _cprintf("The priority level of the thread = %d.\n", dwPriority);

  // �������� ��������� �������� ������
  if (!SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST))
  {
    _cputs("Set thread priority failed.\n");
    _cputs("Press any key to exit.\n");
    _getch();
    return GetLastError();
  }
  // ������ ������� ���������� �������� ������
  dwPriority = GetThreadPriority(hThread);
  _cprintf("The priority level of the thread = %d.\n", dwPriority);

  _cputs("Press any key to exit.\n");
  _getch();

  return 0;
}