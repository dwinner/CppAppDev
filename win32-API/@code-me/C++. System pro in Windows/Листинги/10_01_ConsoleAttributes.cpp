#include <windows.h>
#include <iostream.h>

int main()
{
  char lpszAppName1[] = "C:\\ConsoleProcess.exe";
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  // ��������� ���� ��������� STARTUPINFO
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);
  si.lpTitle = "This is a new title";
  si.dwX = 200;            // ������� ������ ���� ���� �������
  si.dwY = 200;
  si.dwXSize = 300;        // ������� ����
  si.dwYSize = 200;
  si.dwXCountChars = 100;  // ������ ������ ������ �� ����������� 
  si.dwYCountChars = 100;  // ������ ������ ������ �� ���������
  // ������� ����� �� ����� ����
  si.dwFillAttribute = FOREGROUND_RED|FOREGROUND_INTENSITY|
    BACKGROUND_INTENSITY|BACKGROUND_BLUE;
  // ���������� ��� ���������, ��� ����������
  si.dwFlags = STARTF_USECOUNTCHARS|STARTF_USEFILLATTRIBUTE|
    STARTF_USEPOSITION|STARTF_USESHOWWINDOW|
    STARTF_USESIZE;
  si.wShowWindow = SW_SHOWNORMAL;

  // ��������� ������� � ����� ������� ��������
  if (!CreateProcess(lpszAppName1, NULL, NULL, NULL, FALSE,
      CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
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