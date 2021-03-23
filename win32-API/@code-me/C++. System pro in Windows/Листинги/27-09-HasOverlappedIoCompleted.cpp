#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;       // ���������� �����
  HANDLE  hEndWrite;   // ���������� �������
  OVERLAPPED  ovl;     // ��������� ���������� ����������� �������� � �����

  // ������� ������� � �������������� �������
  hEndWrite = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (hEndWrite == NULL)
    return GetLastError();

  // �������������� ��������� OVERLAPPED
  ovl.Offset = 0;          // ������� ����� �������� ����� 0
  ovl.OffsetHigh = 0;      // ������� ����� �������� ����� 0
  ovl.hEvent = hEndWrite;  // ������� ��� ���������� ���������� ������

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

    CloseHandle(hEndWrite);

    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }

  // ����� ������ � ����
  for (int i = 0; i < 10; ++i)
  {
    DWORD  dwBytesWrite;

    if (!WriteFile(
        hFile,         // ���������� �����
        &i,            // ����� ������, ������ ���� ������
        sizeof(i),     // ���������� ������������ ������
        &dwBytesWrite, // ���������� ���������� ������
        &ovl           // ������ �����������
      ))
    {
      cout << "Write file failed." << endl
        << "The last error code: " << GetLastError() << endl;

      return 0;
    }

    // ��������� ���������� ����������� �������� ������
    if (HasOverlappedIoCompleted(&ovl))
      cout << "Write file is completed." << endl;
    else
      cout << "Write file is not completed." << endl;

    // ���� ���������� ����������� �������� ������
    WaitForSingleObject(hEndWrite, INFINITE);
    // ����������� �������� � �����
    ovl.Offset += sizeof(i);
  }
  // ��������� ����������� 
  CloseHandle(hFile);
  CloseHandle(hEndWrite);

  cout << "The file is written." << endl;

  return 0;
}