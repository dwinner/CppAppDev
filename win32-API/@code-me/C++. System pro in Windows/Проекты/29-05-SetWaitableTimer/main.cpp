#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

#define _SECOND 10000000   // ���� ������� ��� ���������� �������

VOID CALLBACK completion_proc(LPVOID lpArg, 
         DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
  // ������� ���������
  cout << "\aThe timer is signaled." << endl;
  // ������������� ���������
  cout << "Arguments: " << (char*)lpArg << endl
    << "Timer low value: " << dwTimerLowValue << endl
    << "Timer high value: " << dwTimerHighValue << endl;
}

int main()
{
  HANDLE  hTimer;            // ��������� ������

  _int64  qwTimeInterval;    // ����� �������� ��� �������

  // ������� ��������� ������
  hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
  if (hTimer == NULL)
    return GetLastError();

  // ����� �������� ��� ������� = 1 �������
  qwTimeInterval = -1 * _SECOND;

  // �������������� ������
  if (!SetWaitableTimer(
    hTimer,              // ���������� �������
    (LARGE_INTEGER*)&qwTimeInterval,   // ��������� ��������
    0,                   // �� ������������� ������
    completion_proc,     // ��������� ����������
    "Demo parameters.",  // ���������� � ���� ��������� ���
    FALSE                // ����� ���������� ������� �� �������������
    ))
  {
    cout << "Set waitable timer failed." << endl
      << "The last error code: " << GetLastError() << endl;

    return 0;
  }
  // ��������� ����� � ������������� ���������
  SleepEx(INFINITE, TRUE);

  // ��������� ������
  CloseHandle(hTimer);

  return 0;
}