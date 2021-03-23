#include <windows.h>
#include <conio.h>

int main()
{
  char lpszComLine1[80] = "C:\\Client1.exe";   // ��� ������� �������
  char lpszComLine2[80] = "C:\\Client2.exe";   // ��� ������� �������

  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  HANDLE hWritePipe, hReadPipe;
  SECURITY_ATTRIBUTES sa;

  // ������������� �������� ������ ������
  sa.nLength = sizeof(SECURITY_ATTRIBUTES);
  sa.lpSecurityDescriptor = NULL;  // ������ �� ���������
  sa.bInheritHandle = TRUE;        // ����������� �����������

  // ������� ��������� �����
  if(!CreatePipe(
      &hReadPipe,  // ���������� ��� ������
      &hWritePipe, // ���������� ��� ������
      &sa,   // �������� ������ �� ���������, ����������� �����������
      0))    // ������ ������ �� ���������
      
  {
    _cputs("Create pipe failed.\n");
    _cputs("Press any key to finish.\n");
    _getch();
    return GetLastError();
  }
  // ������������� �������� ������ ��������
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);
  // ������������ ����������� �����������
  si.dwFlags = STARTF_USESTDHANDLES;
  // ������������� ����������� �����������
  si.hStdInput = hReadPipe;
  si.hStdOutput = hWritePipe;
  si.hStdError = hWritePipe;
  // ��������� ������� �������
  if (!CreateProcess(
      NULL,    // ��� ��������
      lpszComLine1,  // ��������� ������
      NULL,    // �������� ������ �������� �� ���������
      NULL,    // �������� ������ ���������� ������ �� ���������
      TRUE,    // ����������� ����������� �������� ��������
               // ����������� ����� ���������
      CREATE_NEW_CONSOLE,  // ������� ����� �������
      NULL,    // ���������� ����� ��������� �������� ������
      NULL,    // ������� ���� � �������, ��� � � �������� ������
      &si,     // ��� �������� ���� - �� ���������
      &pi      // ����� ����� ����������� � ��������������
               // ������ �������� � ��� ���������� ������
      )
    )
  {
    _cputs("Create process failed.\n");
    _cputs("Press any key to finish.\n");
    _getch();
    return GetLastError();
  }
  // ��������� ����������� ������� �������
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  // ��������� ������� �������
  if (!CreateProcess(
      NULL,    // ��� ��������
      lpszComLine2,  // ��������� ������
      NULL,    // �������� ������ �������� �� ���������
      NULL,    // �������� ������ ���������� ������ �� ���������
      TRUE,    // ����������� ����������� �������� ��������
          // ����������� ����� ���������
      CREATE_NEW_CONSOLE,  // ������� ����� �������
      NULL,    // ���������� ����� ��������� �������� ������
      NULL,    // ������� ���� � �������, ��� � � �������� ������
      &si,     // ��� �������� ���� - �� ���������
      &pi      // ����� ����� ����������� � ��������������
               // ������ �������� � ��� ���������� ������
      )
    )
  {
    _cputs("Create process failed.\n");
    _cputs("Press any key to finish.\n");
    _getch();
    return GetLastError();
  }
  // ��������� ����������� ������� �������
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  // ��������� ����������� ������
  CloseHandle(hReadPipe);
  CloseHandle(hWritePipe);

  _cputs("The clients are created.\n");
  _cputs("Press any key to exit.\n");
  _getch();

  return 0;
}