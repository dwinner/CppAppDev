#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
  // ���������� ����
  if(!ReplaceFile(
    "C:\\demo_file.dat",       // ��� ������������ �����
    "C:\\new_file.dat",        // ��� ����� �����������
    "C:\\back_file.dat",       // ��� ���������� �����
    REPLACEFILE_WRITE_THROUGH, // ���������� ������
    NULL, NULL                 // �� ������������
    ))
  {
    cerr << "Replace file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();
    return 0;
  }

  cout << "The file is replaced." << endl;

  return 0;
}