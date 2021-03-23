#include <windows.h>
#include <fstream.h>

int main()
{
  char    MappingName[] = "MappingName";
  HANDLE  hMapping;      // ���������� �������, ������������� ����
  int    *ptr;           // ��� ��������� �� ������
  const int    n = 10;   // ����������� �������

  cout << "This is a parent process." << endl;
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
  // �������������� ������ � ������� ��� �� �������
  cout  << "Array: ";
  for (int i = 0; i < n; ++i)
  {
    ptr[i] = i;
    cout << ptr[i] << ' ';
  }
  cout << endl;
//----------------------------------------------------------------------
// ������� �������, ������� ����� ������ ������ �� ������������� 
// � ������ �����
  char lpszAppName[] = "C:\\ConsoleProcess.exe";

  STARTUPINFO si;
  PROCESS_INFORMATION piApp;

  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);

  // ������� ����� ���������� �������
  if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
      CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
  {
    cerr << "Create process failed." << endl;
    return GetLastError();
  }
  // ���� ���������� ���������� �������
  WaitForSingleObject(piApp.hProcess, INFINITE);
  // ��������� ����������� ����� �������� � ������� ��������
  CloseHandle(piApp.hThread);
  CloseHandle(piApp.hProcess);
//----------------------------------------------------------------------
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