#include <windows.h>
#include <conio.h>

int main()
{
  char lpszComLine[80];  // ��� ��������� ������

  HANDLE hEnableRead;    // ��� ������������� ������ �������
  char lpszEnableRead[] = "EnableRead";

  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  HANDLE hWritePipe, hReadPipe;
  SECURITY_ATTRIBUTES sa;

  // ������� ������� ��� ������������� ������ �������
  hEnableRead = CreateEvent(NULL, FALSE, FALSE, lpszEnableRead);

  // ������������� �������� ������ ������
  sa.nLength = sizeof(SECURITY_ATTRIBUTES);
  sa.lpSecurityDescriptor = NULL;    // ������ �� ���������
  sa.bInheritHandle = TRUE;          // ����������� �����������

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
  // ��������� ��������� ������
  wsprintf(lpszComLine, "C:\\Client.exe %d %d", 
          (int)hWritePipe, (int)hReadPipe);
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
  _cputs("The process finished reading from the pipe.\n");

  // ���� ������ �� ���������� ������ ��������
  SetEvent(hEnableRead);

  // ����� ����� � ��������� �����
  for (int j = 10; j < 20; j++)
  {
    DWORD dwBytesWritten;
    if (!WriteFile(
        hWritePipe,
        &j,
        sizeof(j),
        &dwBytesWritten,
        NULL))
      {
        _cputs("Write to file failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
      }
    _cprintf("The number %d is written to the pipe.\n", j);
  }
  // ��������� ����������� ������
  CloseHandle(hReadPipe);
  CloseHandle(hWritePipe);
  CloseHandle(hEnableRead);

  _cputs("The process finished writing to the pipe.\n");
  _cputs("Press any key to exit.\n");
  _getch();

  return 0;
}