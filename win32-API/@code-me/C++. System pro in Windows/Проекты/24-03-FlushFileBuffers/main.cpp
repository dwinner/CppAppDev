#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE hFile;
  
  // ������� ���� ��� ������ ������
  hFile = CreateFile(
    "C:\\demo_file.dat",     // ��� �����
    GENERIC_WRITE,           // ������ � ����
    FILE_SHARE_READ,         // ����������� ������ �����
    NULL,                    // ������ ���
    CREATE_ALWAYS,           // ������� ����� ����
    FILE_ATTRIBUTE_NORMAL,   // ������� ����
    NULL                     // ������� ���
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
    // ���� �������� �������� �����, �� ����������� �����
    if(i == 5)
    {
      if(!FlushFileBuffers(hFile))
      {
        cerr << "Flush file buffers failed." << endl
          << "The last error code: " << GetLastError() << endl;
        CloseHandle(hFile);
        cout << "Press any key to finish.";
        cin.get();
        return 0;
      }
      // ������ ����� ����������� ���������� �����
      cout << "A half of the file is written." << endl
        << "Press any key to continue.";
      cin.get();
    }
  }
  // ��������� ���������� ����� 
  CloseHandle(hFile);

  cout << "The file is created and written." << endl;

  return 0;
}