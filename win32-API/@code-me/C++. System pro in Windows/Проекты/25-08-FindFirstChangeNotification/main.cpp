#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hChangeHandle;
  
  // ������� ������ ��������� � ��������
  hChangeHandle = FindFirstChangeNotification(
    "C:\\demo_dir",    // ��� ��������
    TRUE,              // ����������� ����� �����������
    FILE_NOTIFY_CHANGE_FILE_NAME // ����������� ��������� ����� ��������
    | FILE_NOTIFY_CHANGE_SIZE    // � ��������� ��� �������
  );

  if (hChangeHandle == INVALID_HANDLE_VALUE)
  {
    cerr << "Find first change notification failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ����� �������� �������
  cout << "Wait for changes in the directory." << endl;
  // ���� ������� ��������� � ��������
  if (WaitForSingleObject(hChangeHandle, INFINITE) == WAIT_OBJECT_0)
    cout << "First notification: the directory was changed." << endl;
  else
  {
    cerr << "Wait for single object failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ������� ������ ��������� � ��������
  if (!FindNextChangeNotification(hChangeHandle))
  {
    cerr << "Find next change notification failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ���� ������� ��������� � ��������
  if (WaitForSingleObject(hChangeHandle, INFINITE) == WAIT_OBJECT_0)
    cout << "Next notification: the directory was changed." << endl;
  else
  {
    cerr << "Wait for single object failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }
  // ��������� ���������� ������
  FindCloseChangeNotification(hChangeHandle);

  return 0;
}