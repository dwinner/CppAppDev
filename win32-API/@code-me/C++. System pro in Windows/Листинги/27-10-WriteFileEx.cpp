#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

// ��������� ���������� �����-������
VOID  CALLBACK completion_routine(
  DWORD  dwErrorCode,                 // ��� ��������
  DWORD  dwNumberOfBytesTransferred,  // ���������� ���������� ������
  LPOVERLAPPED  lpOverlapped          // ����������� �������� ������
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
  HANDLE  hFile;    // ���������� �����
  OVERLAPPED  ovl;  // ��������� ���������� ����������� �������� � �����

  // �������������� ��������� OVERLAPPED
  ovl.Offset = 0;      // ������� ����� �������� ����� 0
  ovl.OffsetHigh = 0;  // ������� ����� �������� ����� 0

  // ������� ���� ��� ������ ������
  hFile = CreateFile(
    "C:\\demo_file.dat",   // ��� �����
    GENERIC_WRITE,         // ������ � ����
    FILE_SHARE_WRITE,      // ���������� ������ � �����
    NULL,                  // ������ ���
    OPEN_ALWAYS,           // ��������� ��� ������� ����� ����
    FILE_FLAG_OVERLAPPED,  // ����������� ������ � �����
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
  
  // ����� ������ � ����
  for (int i = 0; i < 10; ++i)
  {
    DWORD  dwRet;

    if (!WriteFileEx(
        hFile,       // ���������� �����
        &i,          // ����� ������, ������ ���� ������
        sizeof(i),   // ���������� ������������ ������
        &ovl,        // ������ �����������
        completion_routine // ��������� ����������
      ))
    {
      dwRet = GetLastError();
      if (dwRet == ERROR_IO_PENDING)
        cout << "Write file pending." << endl;
      else
      {
        cout << "Write file failed." << endl
          << "The last error code: " << dwRet << endl;

        return 0;
      }
    }
    // ����, ���� ��������� ����������� ��������� 
    // ���������� �������� ������
    SleepEx(INFINITE, TRUE);
    // ����������� �������� � �����
    ovl.Offset += sizeof(i);
  }
  // ��������� ���������� ����� 
  CloseHandle(hFile);

  cout << "The file is written." << endl;

  return 0;
}