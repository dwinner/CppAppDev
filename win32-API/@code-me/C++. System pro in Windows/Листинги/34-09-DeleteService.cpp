#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";  // ��� �������
  SERVICE_STATUS  service_status;        // ��������� �������
  SC_HANDLE  hServiceControlManager, hService;

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
    SERVICE_ALL_ACCESS | DELETE  // ����� ������ � ������� 
                                 // � �������� �� ���� ������
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

  // �������� ��������� �������
  if (!QueryServiceStatus(hService, &service_status))
  {
    cout << "Query service status failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // ��������� �����������
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }

  // ���� ������ ��������, �� ������������� ���
  if (service_status.dwCurrentState != SERVICE_STOPPED)
  {
    cout << "Service is working. It will be stoped" << endl;
    if (!ControlService(hService, SERVICE_CONTROL_STOP, &service_status))
    {
      cout << "Control service failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
      cin.get();

      // ��������� �����������
      CloseServiceHandle(hServiceControlManager);
      CloseServiceHandle(hService);

      return 0;
    }

    // ����, ���� ������ �����������
    Sleep(500);
  }

  // ������� ������
  if (!DeleteService(hService))
  {
    cout << "Delete service failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // ��������� �����������
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }

  cout << "The service is deleted." << endl
    << "Press any key to exit." << endl;
  cin.get();

  // ��������� �����������
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hService);

  return 0;
}