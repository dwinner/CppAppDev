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
  // ��� ������ �������� � ��������
  char lpszComLine[80]="C:\\ConsoleProcess.exe ";
  // ��� ����������� ������������� �����������
  char lpszHandle[20];

  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  HANDLE  hThread;
  DWORD  IDThread;
  
  _cputs("Press any key to start the count-thread.\n");
  _cputs("After terminating the thread press any key to exit.\n");
  _getch();

  // ��������� �����-�������
  hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 
                          0, &IDThread);
  if (hThread == NULL)
    return GetLastError();

  // ������ ���������� ������ �����������
  if(!SetHandleInformation(
      hThread,               // ���������� ������
      HANDLE_FLAG_INHERIT,   // �������� ������������ �����������
      HANDLE_FLAG_INHERIT))  // ������ ���������� �����������
  {
    _cputs("The inheritance is not changed.\n");
    _cputs("Press any char to finish.\n");
    _getch();
    return GetLastError();
  }

  // ������������� �������� ������ ��������
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb=sizeof(STARTUPINFO);
  // ����������� ���������� � ���������� ������
  _itoa((int)hThread,lpszHandle,10);
  // ������� ��������� ������
  strcat(lpszComLine,lpszHandle);
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

  _getch();

  // ��������� ���������� ������
  CloseHandle(hThread);

  return 0;
}