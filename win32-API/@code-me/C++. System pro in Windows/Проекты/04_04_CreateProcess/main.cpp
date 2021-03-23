#include <windows.h>
#include <iostream.h>

int main()
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  // ��������� �������� ��������� STARTUPINFO �� ���������
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);

  // ��������� ������� Notepad
  if (!CreateProcess(
      NULL,    // ��� �� ������
      "Notepad.exe",  // ��� ���������
      NULL,    // �������� ������ �������� ������������� �� ���������
      NULL,    // �������� ������ ���������� ������ �� ���������
      FALSE,   // ����������� �������� �������� �� �����������
      0,       // �� ��������� NORMAL_PRIORITY_CLASS  
      NULL,    // ���������� ����� ��������� ����������� ��������
      NULL,    // ������� ���� � �������, ��� � � ���������� ��������
      &si,     // ��� �������� ���� - �� ���������
      &pi      // ���������� � ����� ��������
)
    )
  {
    cout << "The mew process is not created." << endl
      << "Check a name of the process." << endl;
    return 0;
  }

  Sleep(1000);  // ������� �������� � �������� ���� ������
  // ������� ����������� ����������� �������� � ������� ��������
  CloseHandle(pi.hThread);
  CloseHandle(pi.hProcess);

  return 0;
}