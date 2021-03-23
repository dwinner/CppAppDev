#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;     // ���������� �����
  OVERLAPPED  ovl;   // ��������� ���������� ����������� �������� � �����

  // �������������� ��������� OVERLAPPED
  ovl.Offset = 0;        // ������� ����� �������� ����� 0
  ovl.OffsetHigh = 0;    // ������� ����� �������� ����� 0
  ovl.hEvent = 0;        // ������� ���

  // ��������� ���� ��� ������
  hFile = CreateFile(
    "C:\\demo_file.dat",   // ��� �����
    GENERIC_READ,          // ������ �� �����
    FILE_SHARE_READ,       // ���������� ������ � �����
    NULL,                  // ������ ���
    OPEN_EXISTING,         // ��������� ������������ ����
    FILE_FLAG_OVERLAPPED,  // ����������� ����
    NULL                   // ������� ���
  );
  // ��������� �� �������� ��������
  if (hFile == INVALID_HANDLE_VALUE)
  {
    cerr << "Create file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();
    return 0;
  }
  // ������ ������ �� �����
  for (;;)
  {
    DWORD  dwBytesRead;
    DWORD  dwRet;
    int    n;

    // ������ ���� ������
    if (!ReadFile(
        hFile,           // ���������� �����
        &n,              // ����� ������, ���� ������ ������
        sizeof(n),       // ���������� �������� ������
        &dwBytesRead,    // ���������� ����������� ������
        &ovl             // ������ �����������
      ))
    {
      switch(dwRet = GetLastError())
      {
      case ERROR_IO_PENDING:
        cout << "Read file pending." << endl;
        break;
      case ERROR_HANDLE_EOF:
        cout << endl << "End of the file." << endl;
        // ��������� ���������� �����
        CloseHandle(hFile);

        cout << "The file is read." << endl;
        return 1;
      default:
        cout << "Read file failed." << endl
          << "The last error code: " << dwRet << endl;
        return 0;
      }
    }
    // ����, ���� ���������� ����������� �������� ������
    WaitForSingleObject(hFile, INFINITE);
    // �������� �����
    cout << n << ' ';
    // ����������� �������� � �����
    ovl.Offset += sizeof(n);
  }
}