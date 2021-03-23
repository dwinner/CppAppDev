#include <windows.h>
#include <iostream.h>

// ��������� ���������� �����-������
VOID  CALLBACK completion_routine(
    DWORD  dwErrorCode,                // ��� ��������
    DWORD  dwNumberOfBytesTransferred, // ���������� ���������� ������
    LPOVERLAPPED  lpOverlapped         // ����������� �������� ������
    )
{
  cout << "Completion routine parameters: " << endl
    << "\tErrorCode: " << dwErrorCode << endl
    << "\tNumber of bytes transferred: " << dwNumberOfBytesTransferred << endl
    << "\tOffsets: " << (*lpOverlapped).OffsetHigh << ' '
    << (*lpOverlapped).Offset << endl;
}

// ������� ���������
int main()
{
  HANDLE  hFile;     // ���������� �����
  OVERLAPPED  ovl;   // ��������� ���������� ����������� �������� � �����

  // �������������� ��������� OVERLAPPED
  ovl.Offset = 0;      // ������� ����� �������� ����� 0
  ovl.OffsetHigh = 0;  // ������� ����� �������� ����� 0

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
    DWORD  dwRet;
    int    n;

    // ������ ���� ������
    if (!ReadFileEx(
        hFile,       // ���������� �����
        &n,          // ����� ������, ���� ������ ������
        sizeof(n),   // ���������� �������� ������
        &ovl,        // ������ �����������
        completion_routine   // ��������� ���������� ������
      ))
    {
      switch(dwRet = GetLastError())
      {
      case ERROR_IO_PENDING:
        cout << "Read file pending." << endl;
        break;
      case ERROR_HANDLE_EOF:
        cout << endl << "End of the file." << endl;
        cout << "The file is read." << endl;
        // ��������� ���������� �����
        CloseHandle(hFile);

        return 0;
      default:
        cout << "Read file failed." << endl
          << "The last error code: " << dwRet << endl;

        // ��������� ���������� �����
        CloseHandle(hFile);

        return 0;
      }
    }
    // ����, ���� ��������� ����������� ��������� ���������� ������
    SleepEx(INFINITE, TRUE);
    // �������� �����
    cout << n << endl;
    // ����������� �������� � �����
    ovl.Offset += sizeof(n);
  }
}