#include <windows.h>
#include <conio.h>

int main(int argc, char *argv[])
{
  HANDLE hWritePipe;

  // ����������� ���������� ������������� ����������� � �����
  hWritePipe = (HANDLE)atoi(argv[1]);
  // ���� ������� � ������ ������ � ��������� �����
  _cputs("Press any key to start communication.\n");
  _getch();
  // ����� � ��������� �����
  for (int i = 0; i < 10; i++)
  {
    DWORD dwBytesWritten;
    if (!WriteFile(
        hWritePipe,
        &i,
        sizeof(i),
        &dwBytesWritten,
        NULL))
      {
        _cputs("Write to file failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
      }
    _cprintf("The number %d is written to the pipe.\n", i);
    Sleep(500);
  }
  // ��������� ���������� ������
  CloseHandle(hWritePipe);

  _cputs("The process finished writing to the pipe.\n");
  _cputs("Press any key to exit.\n");
  _getch();

  return 0;
}