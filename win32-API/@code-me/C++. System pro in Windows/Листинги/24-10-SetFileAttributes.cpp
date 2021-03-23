#include <windows.h>
#include <iostream.h>

int main()
{
  DWORD  file_attr;

  // ������ �������� �����
  file_attr = GetFileAttributes("C:\\demo_file.dat");
  if(file_attr == -1)
  {
    cerr << "Get file attributes failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();
    return 0;
  }
  // ���������, �������� �� ���� ����������
  if(file_attr == FILE_ATTRIBUTE_NORMAL)
    cout << "This is a normal file." << endl;
  else
  {
    cout << "This is a not normal file." << endl;
    return 0;
  }
  // ������������� ������� �������� �����
  if(!SetFileAttributes("C:\\demo_file.dat", FILE_ATTRIBUTE_HIDDEN))
  {
    cerr << "Set file attributes failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ������ ����� ���������, ��� ���� �������
  cout << "Now the file is hidden." << endl
    << "Press any key to continue.";
  cin.get();
  // ������� ������ ���� �������
  if(!SetFileAttributes("C:\\demo_file.dat", FILE_ATTRIBUTE_NORMAL))
  {
    cerr << "Set file attributes failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  cout << "Now the file is again normal." << endl;
  
  return 0;
}