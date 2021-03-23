#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hFindFile;
  WIN32_FIND_DATA  fd;

  // ������� ������ ����
  hFindFile = FindFirstFile("C:\\demo_dir\\*", &fd);
  if (hFindFile == INVALID_HANDLE_VALUE)
  {
    cerr << "Find first file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ������� �� ������� ��� ������� �����
  cout << "The first file name: " << fd.cFileName << endl;
  // ������� ��������� ���� � ������� �� ������� ��� ���
  while (FindNextFile(hFindFile, &fd))
    cout << "The next file name: " << fd.cFileName << endl;
  // ��������� ���������� ������
  FindClose(hFindFile);

  return 0;
}