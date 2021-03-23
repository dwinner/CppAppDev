#include <windows.h>
#include <iostream.h>

HANDLE hInEvent;
CHAR lpEventName[] = "InEventName";

int main()
{
  DWORD dwWaitResult;

  char szAppName[] = "C:\\ConsoleProcess.exe";
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  // ������ �������, ���������� ���� �������
  hInEvent = CreateEvent(NULL, FALSE, FALSE, lpEventName);
  if (hInEvent == NULL)
    return GetLastError();

  // ��������� �������, ������� ���� ���� �������
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);
  if (!CreateProcess(szAppName, NULL, NULL, NULL, FALSE,
      CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    return 0;
  // ��������� ����������� ����� ��������
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  // ���� ���������� � ����������� ������� � ����� �������
  dwWaitResult = WaitForSingleObject(hInEvent, INFINITE);
  if (dwWaitResult != WAIT_OBJECT_0)
    return dwWaitResult;

  cout << "A symbol has got." << endl;

  CloseHandle(hInEvent);

  cout << "Press any key to exit.";
  cin.get();

  return 0;
}