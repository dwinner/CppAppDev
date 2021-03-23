#include <windows.h>
#include <iostream.h>

int main()
{
  char lpszAppName[] = "C:\\ConsoleProcess.exe";

  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  // ��������� ���� ��������� STARTUPINFO
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);
  si.lpTitle = "This is a new title";
  si.dwX = 200;            // ������� ������ ���� ���� �������
  si.dwY = 200;
  si.dwXSize = 200;        // ������� ����
  si.dwYSize = 100;
  si.dwXCountChars = 150;  // ������ ������ ������ �� ����������� 
  si.dwYCountChars = 50;   // ������ ������ ������ �� ���������
  // ������� ����� �� ����� ����
  si.dwFillAttribute = FOREGROUND_RED|FOREGROUND_INTENSITY|
  BACKGROUND_BLUE|BACKGROUND_INTENSITY;
  // ���������� ��� ���������, ��� ����������
  si.dwFlags = STARTF_USECOUNTCHARS|STARTF_USEFILLATTRIBUTE|
  STARTF_USEPOSITION|STARTF_USESIZE;
  si.wShowWindow = SW_SHOWNORMAL;

  // ��������� �������, ������� ��� ������������ �������
  if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
    DETACHED_PROCESS, NULL, NULL, &si, &pi))
  {
    cout << "The new process is not created." << endl
      << "Check a name of the process." << endl
      << "Press any key to finish." << endl;
    cin.get();

    return 0;
  }
  // ��������� ����������� ��������
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  return 0;
}