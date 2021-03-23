#include <windows.h>
#include <conio.h>

int main()
{
  char lpszComLine[80];  // ��� ��������� ������

  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  HANDLE hWritePipe, hReadPipe, hInheritWritePipe;

  // ������� ��������� �����
  if(!CreatePipe(
      &hReadPipe,    // ���������� ��� ������
      &hWritePipe,   // ���������� ��� ������
      NULL,          // �������� ������ �� ���������, � ���� ������ 
                     // ����������� hReadPipe � hWritePipe �������������
      0))            // ������ ������ �� ���������
      
  {
    _cputs("Create pipe failed.\n");
    _cputs("Press any key to finish.\n");
    _getch();
    return GetLastError();
  }
  // ������ ����������� �������� ����������� hWritePipe
  if(!DuplicateHandle(
      GetCurrentProcess(),   // ���������� �������� ��������
      hWritePipe,            // �������� ���������� ������
      GetCurrentProcess(),   // ���������� �������� ��������
      &hInheritWritePipe,    // ����� ���������� ������
      0,                     // ���� �������� ������������
      TRUE,                  // ����� ���������� �����������
      DUPLICATE_SAME_ACCESS ))  // ������ �� ��������
  {
    _cputs("Duplicate handle failed.\n");
    _cputs("Press any key to finish.\n");
    _getch();
    return GetLastError();
  }
  // ��������� �������� ����������
  CloseHandle(hWritePipe);
  // ������������� �������� ������ ��������
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);
  // ��������� ��������� ������
  wsprintf(lpszComLine, "C:\\Client.exe %d", (int)hInheritWritePipe);
  // ��������� ����� ���������� �������
  if (!CreateProcess(
      NULL,    // ��� ��������
      lpszComLine,   // ��������� ������
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
      ))
    {
      _cputs("Create process failed.\n");
      _cputs("Press any key to finish.\n");
      _getch();
      return GetLastError();
    }
  // ��������� ����������� ������ ��������
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  // ��������� �������� ���������� ������
  CloseHandle(hInheritWritePipe);
  // ������ �� ���������� ������
  for (int i = 0; i < 10; i++)
  {
    int nData;
    DWORD dwBytesRead;
    if (!ReadFile(
        hReadPipe,
        &nData,
        sizeof(nData),
        &dwBytesRead,
        NULL))
      {
        _cputs("Read from the pipe failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
      }
    _cprintf("The number %d is read from the pipe.\n", nData);
  }
  // ��������� ���������� ������
  CloseHandle(hReadPipe);

  _cputs("The process finished reading from the pipe.\n");
  _cputs("Press any key to exit.\n");
  _getch();

  return 0;
}