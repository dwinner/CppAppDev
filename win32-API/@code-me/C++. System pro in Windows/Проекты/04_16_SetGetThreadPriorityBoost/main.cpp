#include <windows.h>
#include <conio.h>

int main()
{
  HANDLE  hProcess, hThread;
  BOOL    bPriorityBoost;

  // �������� ���������������� �������� ��������
  hProcess = GetCurrentProcess();

  // ������ ����� ������������� ��������� ����������� ��� ��������
  if (!GetProcessPriorityBoost(hProcess, &bPriorityBoost))
  {
    _cputs("Get process priority boost failed.\n");
    _cputs("Press any key to exit.\n");
    _getch();
    return GetLastError();
  }
  _cprintf("The process priority boost = %d.\n", bPriorityBoost);

  // ��������� ����� ������������� ��������� ����������� ��� ��������
  if (!SetProcessPriorityBoost(hProcess, TRUE))
  {
    _cputs("Set process priority boost failed.\n");
    _cputs("Press any key to exit.\n");
    _getch();
    return GetLastError();
  }

  // �������� ���������������� �������� ������
  hThread = GetCurrentThread();
  // ������ ����� ������������� ��������� ����������� ��� ������
  if (!GetThreadPriorityBoost(hThread, &bPriorityBoost))
  {
    _cputs("Get process priority boost failed.\n");
    _cputs("Press any key to exit.\n");
    _getch();
    return GetLastError();
  }
  _cprintf("The thread priority boost = %d.\n", bPriorityBoost);

  // �������� ����� ������������� ��������� ����������� ��� ������
  if (!SetThreadPriorityBoost(hThread, FALSE))
  {
    _cputs("Set process priority boost failed.\n");
    _cputs("Press any key to exit.\n");
    _getch();
    return GetLastError();
  }
  _cputs("Press any key to exit.\n");
  _getch();

  return 0;
}