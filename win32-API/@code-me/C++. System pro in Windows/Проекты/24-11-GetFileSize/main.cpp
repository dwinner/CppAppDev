#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;
  DWORD  dwFileSize;   // ������� ����� ������� �����

  // ��������� ���� ��� ������
  hFile = CreateFile(
    "C:\\demo_file.dat",   // ��� �����
    GENERIC_READ,          // ������ �� �����
    0,                     // ����������� ������ � �����
    NULL,                  // ������ ��� 
    OPEN_EXISTING,         // ��������� ������������ ����
    FILE_ATTRIBUTE_NORMAL, // ������� ����
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
  
  // ���������� ������ �����
  dwFileSize = GetFileSize(hFile, NULL);
  if (dwFileSize == -1)
  {
    cerr << "Get file size failed." << endl
      << "The last error code: " << GetLastError() << endl;
    CloseHandle(hFile);
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ������� ������ �����
  cout << "File size: " << dwFileSize << endl;
  // ��������� ���������� ����� 
  CloseHandle(hFile);

  return 0;
}