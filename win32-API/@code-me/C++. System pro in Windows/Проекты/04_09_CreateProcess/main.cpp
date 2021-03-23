#include <windows.h>
#include <conio.h>

volatile int count;

void thread()
{
  for (;;)
  {
    count++;
    Sleep(500);
    _cprintf ("count = %d\n", count);
  }
}

int main()
{
  char lpszComLine[80];  // ��� ��������� ������

  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  SECURITY_ATTRIBUTES sa;

  HANDLE  hThread;
  DWORD  IDThread;

  _cputs("Press any key to start the count-thread.\n");
  _getch();

  // ������������� �������� ������ ������
  sa.nLength = sizeof(SECURITY_ATTRIBUTES);
  sa.lpSecurityDescriptor = NULL;    // ������ �� ���������
  sa.bInheritHandle = TRUE;          // ���������� ������ �����������
  
  // ��������� �����-�������
  hThread = CreateThread(&sa, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, 
                          &IDThread);
  if (hThread == NULL)
    return GetLastError();

  // ������������� �������� ������ ��������
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb=sizeof(STARTUPINFO);
  // ��������� ��������� ������
  wsprintf(lpszComLine, "C:\\ConsoleProcess.exe %d", (int)hThread); 
  // ��������� ����� ���������� �������
  if (!CreateProcess(
      NULL,    // ��� ��������
      lpszComLine,  // ����� ��������� ������
      NULL,    // �������� ������ �������� �� ���������
      NULL,    // �������� ������ ���������� ������ �� ���������
      TRUE,    // ����������� ����������� �������� ��������
               // ����������� ����� ���������
      CREATE_NEW_CONSOLE,  // ����� �������  
      NULL,    // ���������� ����� ��������� �������� ������
      NULL,    // ������� ���� � �������, ��� � � �������� ������
      &si,     // ��� �������� ���� - �� ���������
      &pi      // ����� ����� ����������� � ��������������
               // ������ �������� � ��� ���������� ������
      )
    )
  {
    _cputs("The new process is not created.\n");
    _cputs("Press any key to finish.\n");
    _getch();
    return GetLastError();
  }
  // ��������� ����������� ������ ��������
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  // ���� �������� ������-��������
  WaitForSingleObject(hThread, INFINITE);
  _cputs("Press any key to exit.\n");
  _getch();
  // ��������� ���������� ������
  CloseHandle(hThread);

  return 0;
}