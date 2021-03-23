#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE hFile;
  
  // ������� ���� ��� ������ ������
  hFile = CreateFile(
    "C:\\demo_file.dat",   // ��� �����
    GENERIC_WRITE,         // ������ � ����
    0,                     // ����������� ������ � �����
    NULL,                  // ������ ��� 
    CREATE_NEW,            // ������� ����� ����
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
  
  // ����� ������ � ����
  for (int i = 0; i < 10; ++i)
  {
    DWORD dwBytesWrite;

    if (!WriteFile(
        hFile,               // ���������� �����
        &i,                  // ����� ������, ������ ���� ������
        sizeof(i),           // ���������� ������������ ������
        &dwBytesWrite,       // ���������� ���������� ������
        (LPOVERLAPPED)NULL   // ������ ����������
      ))
    {
      cerr << "Write file failed." << endl
        << "The last error code: " << GetLastError() << endl;
      CloseHandle(hFile);
      cout << "Press any key to finish.";
      cin.get();
      return 0;
    }
  }
  // ��������� ���������� ����� 
  CloseHandle(hFile);

  cout << "The file is created and written." << endl;

  return 0;
}