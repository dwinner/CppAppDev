#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";    // ��� �������
  SC_HANDLE  hServiceControlManager, hService;
  
  // ��������� �� ����� ��� ���������� � ������������ �������
  QUERY_SERVICE_CONFIG*  lpQueryServiceConfig;
  // ���������� ��� ������� ��������� � ������ ������� �������
  DWORD  dwBytesNeeded;

  // ����������� � ���������� ��������
  hServiceControlManager = OpenSCManager(
    NULL,      // ��������� ������
    NULL,      // �������� ���� ������ ��������
    SC_MANAGER_CONNECT   // ���������� � ���������� ��������
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

  // ��������� ������
  hService = OpenService(
    hServiceControlManager,  // ���������� ��������� ��������
    service_name,            // ��� �������
    SERVICE_ALL_ACCESS       // ����� ������ � �������
  );
  if (hService == NULL)
  {
    cout << "Open service failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // ��������� ���������� ��������� ��������
    CloseServiceHandle(hServiceControlManager);

    return 0;
  }

  cout << "Service is opened." << endl
    << "Press any key to continue." << endl;
  cin.get();

  // ����������� ������ ��� �����
  lpQueryServiceConfig = (LPQUERY_SERVICE_CONFIG)new char[4096];

  // ���������� ������������ �������
  if (!QueryServiceConfig(
    hService,              // ���������� �������
    lpQueryServiceConfig,  // ����� ��������� ������������ �������
    4096,                  // ������ ���� ���������
    &dwBytesNeeded         // ����������� ���������� ������
    ))
  {
    cout << "Query service configuartion failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // ��������� �����������
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }
  // ������������� ���������� � ������������
  cout << "Service type: " << lpQueryServiceConfig->dwServiceType << endl
    << "Start type: " << lpQueryServiceConfig->dwStartType << endl
    << "Error control: " << lpQueryServiceConfig->dwErrorControl << endl
    << "Binary path name: " << lpQueryServiceConfig->lpBinaryPathName 
    << endl
    << "Service start name: " << lpQueryServiceConfig->lpServiceStartName 
    << endl
    << "Display name: " << lpQueryServiceConfig->lpDisplayName << endl
    << endl;
  // ����������� ������
  delete[] lpQueryServiceConfig;

  cout << "Press any key to exit." << endl;
  cin.get();

  // ��������� �����������
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hService);

  return 0;
}