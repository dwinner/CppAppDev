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

  // ��������� ������������ �������
  QueryServiceConfig( hService, lpQueryServiceConfig, 4096, 
                      &dwBytesNeeded);
  // ������������� ���������� � ������ ������� �������
  cout << "Old start type: " << lpQueryServiceConfig->dwStartType 
       << endl;

  // �������� ����� ������� �������
  if (!ChangeServiceConfig(
    hService,              // ���������� �������
    SERVICE_NO_CHANGE,     // ��� ������� �� ��������
    SERVICE_AUTO_START,    // ������ �� ����� �������� �������
    SERVICE_NO_CHANGE,     // ����� ��������� ������ �� ��������
    NULL, NULL, NULL, NULL, NULL, NULL, NULL  // ��� ��������� ��������� 
                                              // ������������ �� ��������
    ))
  {
    cout << "Change service configuration failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // ��������� �����������
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }

  // ��������� ������������ �������
  QueryServiceConfig( hService, lpQueryServiceConfig, 4096, 
                     &dwBytesNeeded);
  // ������������� ���������� � ������ ������� �������
  cout << "New start type: " << lpQueryServiceConfig->dwStartType 
       << endl;

  // ��������������� ����� ������� �������
  ChangeServiceConfig(
    hService,              // ���������� �������
    SERVICE_NO_CHANGE,     // ��� ������� �� ��������
    SERVICE_DEMAND_START,  // ������ �� ����� �������� ��������� ����������
    SERVICE_NO_CHANGE,     // ����� ��������� ������ �� ��������
    NULL, NULL, NULL, NULL, NULL, NULL, NULL  // ��� ��������� ��������� 
                                              // ������������ �� ��������
    );
  // ��������� ������������ �������
  QueryServiceConfig( hService, lpQueryServiceConfig, 4096, 
                     &dwBytesNeeded);
  // ������������� ���������� � ������ ������� �������
  cout << "Old start type: " << lpQueryServiceConfig->dwStartType 
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