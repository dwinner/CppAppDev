#include <windows.h>
#include <fstream.h>

int main()
{
  char  MappingName[] = "MappingName";
  HANDLE  hMapping;      // ���������� �������, ������������� ����
  int    *ptr;           // ��� ��������� �� ������
  const int    n = 10;   // ����������� �������

  cout << "This is a child process." << endl;
  // ��������� ������ ����������� ����� � ������
  hMapping = CreateFileMapping(
        INVALID_HANDLE_VALUE,  // ���� �������� �������
        NULL,            // �������� ������ �� ���������
        PAGE_READWRITE,  // ����� �������: ������ � ������
        0,               // ������� ����� = 0
        n * sizeof(int), // ������� ����� = ����� �������
        MappingName);    // ��� ������� �����������
  if (!hMapping)
  {
    cerr << "Create file mapping failed." << endl;
    return GetLastError();
  }
  // ������� ��� �����
  ptr = (int*)MapViewOfFile(
      hMapping,        // ���������� ������� �����������
      FILE_MAP_WRITE,  // ����� ������� � ����
      0,0,             // ���������� ���� � ������
      0);              // ���������� ���� ����
  // ������� ������ �� ���� �� �������
  cout  << "Array: ";
  for (int i = 0; i < n; ++i)
    cout << ptr[i] << ' ';
  cout << endl;
  // �������� ����������� ����� � ������
  if (!UnmapViewOfFile(ptr))
  {
    cerr << "Unmap view of file failed." << endl;
    return GetLastError();
  }
  // ��������� ������ ����������� ����� � ������
  if (!CloseHandle(hMapping))
  {
    cerr << "Close file failed." << endl;
    return GetLastError();
  }
  // ���� ������� �� ���������� ��������
  char  c;
  cout << "Input any char to exit: ";
  cin >> c;

  return 0;
}