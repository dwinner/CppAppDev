#include <windows.h>
#include <iostream.h>

int main()
{
  DWORD  dwNumberOfChar;
  char  szDirName[MAX_PATH];

  // ���������� ��� �������� ��������
  dwNumberOfChar = GetCurrentDirectory(MAX_PATH, szDirName);
  if (dwNumberOfChar == 0)
  {
    cerr << "Get current directory failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ������� �� ������� ��� �������� ��������
  cout << "Current directory name: " << szDirName << endl;
  // ������������� ������� ������� ��� �������� �� ���� ������
  if (!SetCurrentDirectory("C:\\demo_dir"))
  {
    cerr << "Set current directory failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ���������� ��� ������ �������� ��������
  dwNumberOfChar = GetCurrentDirectory(MAX_PATH, szDirName);
  if (dwNumberOfChar == 0)
  {
    cerr << "Get current directory failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ������� �� ������� ��� ������ �������� ��������
  cout << "Current directory name: " << szDirName << endl;

  return 0;
}