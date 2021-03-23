#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";  // ��� �������
  SC_HANDLE  hServiceControlManager;  // ���������� ���� ������ ��������
  SC_LOCK    hScLock;  // ���������� ���������� ���� ������ ��������

  // ��������� �� ����� ��� ��������� � ����������
  LPQUERY_SERVICE_LOCK_STATUS    lpLockStatus;
  // ����� ������
  DWORD  dwBufferSize;
  // ���������� ��� ����� ������ � ������ ������� �������
  DWORD  dwBytesNeeded;

  // ����������� � ���������� ��������
  hServiceControlManager = OpenSCManager(
    NULL,      // ��������� ������
    NULL,      // �������� ���� ������ ��������
    SC_MANAGER_LOCK |              // ��������� ���������� ���� ������ 
    SC_MANAGER_QUERY_LOCK_STATUS   // � ����������� ��������� ����������
    );
  if (hServiceControlManager == NULL)
  {
    cout << "Open service control manager failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to continue." << endl;
    cin.get(); 

    return 0;
  }

  cout << "Service control manager is opened." << endl
    << "Press any key to continue." << endl;
  cin.get();

  // ��������� ���� ������ ��������
  hScLock = LockServiceDatabase(hServiceControlManager);
  if (hScLock == NULL)
  {
    cout << "Lock service database failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // ��������� ���������� ���� ������ ��������
    CloseServiceHandle(hServiceControlManager);

    return 0;
  }

  cout << "\tThe service database is locked." << endl;

  // ����������� ������ ��� �����
  dwBufferSize = 4096;
  lpLockStatus = (LPQUERY_SERVICE_LOCK_STATUS)new char[dwBufferSize];
  // ���������� ��������� ����������
  QueryServiceLockStatus(hServiceControlManager, lpLockStatus, 
                         dwBufferSize, &dwBytesNeeded);
  // ������� �� ������� ��������� ����������
  cout << "Lock state: " << lpLockStatus->fIsLocked << endl
    << "Lock owner: " << lpLockStatus->lpLockOwner << endl
    << "Lock duration: " << lpLockStatus->dwLockDuration << endl;

  // ������������ ���� ������ ��������
  UnlockServiceDatabase(hScLock);

  cout << "\tThe service database is unlocked." << endl;

  // ���������� ��������� ����������
  QueryServiceLockStatus(hServiceControlManager, lpLockStatus, 
                         dwBufferSize, &dwBytesNeeded);
  // ������� �� ������� ��������� ����������
  cout << "Lock state: " << lpLockStatus->fIsLocked << endl
    << "Lock owner: " << lpLockStatus->lpLockOwner << endl
    << "Lock duration: " << lpLockStatus->dwLockDuration << endl;

  cout << "Press any key to exit." << endl;
  cin.get();

  // ��������� �����������
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hScLock);

  return 0;
}