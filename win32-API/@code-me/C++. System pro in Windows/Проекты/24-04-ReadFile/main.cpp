#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFile;

  // ��������� ���� ��� ������
  hFile = CreateFile(
    "C:\\demo_file.dat",     // ��� �����
    GENERIC_READ,            // ������ �� �����
    0,                       // ����������� ������ � �����
    NULL,                    // ������ ��� 
    OPEN_EXISTING,           // ��������� ������������ ����
    FILE_ATTRIBUTE_NORMAL,   // ������� ����
    NULL        // ������� ���
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
    int    n;
    
    // ������ ���� ������
    if (!ReadFile(
        hFile,               // ���������� �����
        &n,                  // ����� ������, ���� ������ ������
        sizeof(n),           // ���������� �������� ������
        &dwBytesRead,        // ���������� ����������� ������
        (LPOVERLAPPED)NULL   // ������ ����������
      ))
    {
      cerr << "Read file failed." << endl
        << "The last error code: " << GetLastError() << endl;
      CloseHandle(hFile);
      cout << "Press any key to finish.";
      cin.get();
      return 0;
    }
    // ��������� �� ����� �����
    if (dwBytesRead == 0)
      // ���� ��, �� ������� �� �����
      break;
    else
      // ����� ������� ������ �� �������
      cout << n << ' ';
  }

  cout << endl;

  // ��������� ���������� ����� 
  CloseHandle(hFile);

  cout << "The file is opened and read." << endl;

  return 0;
}