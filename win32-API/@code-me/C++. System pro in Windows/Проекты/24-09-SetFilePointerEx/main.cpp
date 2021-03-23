
// #define _WIN32_WINNT 0x0500  // ��� ���������� ���� ������ ������ �������, ���� ����� ���������

#include <windows.h>
#include <iostream>
using namespace std;

extern "C" WINBASEAPI BOOL WINAPI SetFilePointerEx(
    HANDLE hFile,
    LARGE_INTEGER liDistanceToMove,
    PLARGE_INTEGER lpNewFilePointer,
    DWORD dwMoveMethod
    );

int main()
{
  HANDLE  hFile;        // ���������� �����
  int     n;            // ��� ������ ������
  LARGE_INTEGER  p, q;  // ��� ��������� �������
  DWORD dwBytesRead;    // ���������� ����������� ������
  int     m;            // ����������� �����
  
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

  // ������ ����� ������ ������
  cout << "Input a number from 0 to 9: ";
  cin >> n;
  q.HighPart = 0;
  q.LowPart = n * sizeof(int);
  // �������� ��������� ������� �����
  if(!SetFilePointerEx(hFile, q, &p, FILE_BEGIN))
  {
    cerr << "Set file pointer failed." << endl
      << "The last error code: " << GetLastError() << endl;
    CloseHandle(hFile);
    cout << "Press any key to finish.";
    cin.get();
    return 0;
  }
  // ������� �� ������� �������� ��������� ������� �����
  cout << "File pointer: " << p.HighPart << ' ' << p.LowPart << endl;
  // ������ ������ �� �����
  if (!ReadFile(
      hFile,             // ���������� �����
      &m,                // ����� ������, ���� ������ ������
      sizeof(m),         // ���������� �������� ������
      &dwBytesRead,      // ���������� ����������� ������
      (LPOVERLAPPED)NULL // ������ ����������
    ))
  {
    cerr << "Read file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    CloseHandle(hFile);
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ������� ����������� ����� �� �������
  cout << "The read number: " << m << endl;
  // ��������� ���������� ����� 
  CloseHandle(hFile);

  return 0;
}