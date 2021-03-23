#include <windows.h>
#include <iostream.h>
#include <stdio.h>

int main()
{
  HANDLE  hFindFile;
  WIN32_FIND_DATA  fd;
  char  szFullFileName[MAX_PATH];

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
  // ������� �� �������� �����
  while (FindNextFile(hFindFile, &fd))
  {
    // ���� ��� �� ����������, �� ������� ���
    if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
      // ��������� ��� �����
      sprintf(szFullFileName, "C:\\demo_dir\\%s", fd.cFileName);
      // ������� ����
      if (!DeleteFile(szFullFileName))
      {
        cerr << "Delete file failed." << endl
          << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();

        return 0;
      }
      else
        cout << "The next file: " << fd.cFileName << " is deleted." << endl;
    }
    else
      cout << "The next directory: " << fd.cFileName << " is not deleted." << endl;
  }
  // ��������� ���������� ������
  if (!FindClose(hFindFile))
  {
	  cout << "Find close failed." << endl;
	  return 0;
  }
  // ������� �������
  if (!RemoveDirectory("C:\\demo_dir"))
  {
    cerr << "Remove directory failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }

  cout << "The directory is removed." << endl;

  // ��������� ���������� ������
  FindClose(hFindFile);

  return 0;
}