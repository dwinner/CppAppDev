#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

#define _SECOND 10000000   // ���� ������� ��� ���������� �������

int main()
{
  HANDLE  hTimer;          // ��������� ������

  _int64  qwTimeInterval;  // ����� �������� ��� �������

  // ������� ��������� ������
  hTimer = CreateWaitableTimer(NULL, FALSE, "demo_timer");
  if (hTimer == NULL)
    return GetLastError();

  // ����� �������� ��� ������� = 2 �������
  qwTimeInterval = -2 * _SECOND;

  // �������������� ������
  if (!SetWaitableTimer(
    hTimer,  // ���������� �������
    (LARGE_INTEGER*)&qwTimeInterval,  // ��������� ��������
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

  // ������� ����� ���������� �������
  char lpszAppName[] = "C:\\DemoProcess.exe";

  STARTUPINFO si;
  PROCESS_INFORMATION piApp;

  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);

  if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
      CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
  {
    cout << "The new process is not created." << endl
      << "Check a name of the process." << endl
      << "Press any key to finish." << endl;

    cin.get();

    return 0;
  }

  // ���� ���������� ���������� ��������
  WaitForSingleObject(piApp.hProcess, INFINITE);
  // ��������� ����������� ����� �������� � ������� ��������
  CloseHandle(piApp.hThread);
  CloseHandle(piApp.hProcess);

  // ��������� ������
  CloseHandle(hTimer);

  return 0;
}