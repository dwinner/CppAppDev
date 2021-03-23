#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

#define _SECOND 10000000   // ���� ������� ��� ���������� �������

HANDLE  hTimer;    // ��������� ������

DWORD WINAPI thread(LPVOID)
{
  // ���� ������ �� ���������� �������
  WaitForSingleObject(hTimer, INFINITE);
  // ������� ���������
  cout << "\aThe timer is signaled." << endl;

  return 0;
}

int main()
{
  HANDLE  hThread;
  DWORD  IDThread;

  _int64  qwTimeInterval;    // ����� �������� ��� �������

  // ������� ��������� ������
  hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
  if (hTimer == NULL)
    return GetLastError();

  // ����� �������� ��� ������� = 3 �������
  qwTimeInterval = -3 * _SECOND;

  // �������������� ������
  if (!SetWaitableTimer(
    hTimer,  // ���������� �������
    (LARGE_INTEGER*)&qwTimeInterval,   // ��������� ��������
    0,       // �� ������������� ������
    NULL,    // ��������� ���������� ���
    NULL,    // ���������� � ���� ��������� ���
    FALSE    // ����� ���������� ������� �� �������������
    ))
  {
    cout << "Set waitable timer failed." << endl
      << "The last error code: " << GetLastError() << endl;

    return 0;
  }

  // ��������� �����
  hThread = CreateThread(NULL, 0, thread, NULL, 0, &IDThread);
  if (hThread == NULL)
    return GetLastError();

  // ����, ���� ����� �������� ������
  WaitForSingleObject(hThread, INFINITE);
  // ��������� �����������
  CloseHandle(hThread);
  CloseHandle(hTimer);

  return 0;
}