#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";    // ��� �������
  SC_HANDLE  hServiceControlManager, hService;
  SERVICE_STATUS  service_status;

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

  // ����������� ��������� �������
  if (!QueryServiceStatus(
    hService,        // ���������� �������
    &service_status  // ����� ��������� ��������� �������
    ))
  {
    cout << "Query service sataus failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // ��������� �����������
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }

  switch (service_status.dwCurrentState)
  {
  case SERVICE_STOPPED:
    cout << "The service is stopped." << endl;
    break;
  case SERVICE_RUNNING:
    cout << "The service is running." << endl;
    break;
  default:
    cout << "The service status: " << service_status.dwCurrentState 
        << endl;
    break;
  }

  cout << "Press any key to exit." << endl;
  cin.get();

  // ��������� �����������
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hService);

  return 0;
}