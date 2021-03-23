#include <windows.h>
#include <iostream.h>

int main()
{
  SC_HANDLE  hServiceControlManager, hService;

  // ����������� � ���������� ��������
  hServiceControlManager = OpenSCManager(
    NULL,      // ��������� ������
    NULL,      // �������� ���� ������ ��������
    SC_MANAGER_CREATE_SERVICE  // �������� �������� �������
    );
  if (hServiceControlManager == NULL)
  {
    cout << "Open service control manager failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get(); 

    return 0;
  }
  cout << "Service control manager is opened." << endl
    << "Press any key to continue." << endl;
  cin.get();

  // ������������� ����� ������
  hService = CreateService(
    hServiceControlManager,  // ���������� ��������� ��������
    "DemoService",           // ���������� ��� �������, ������������ SCM
    "Demo_Service",          // ������� ��� ������� � ������ ����������
    SERVICE_ALL_ACCESS,      // ������ �������� ��� ��������
    SERVICE_WIN32_OWN_PROCESS,   // ������ �������� ���������
    SERVICE_DEMAND_START,    // ����������� ������ �� ����������
    SERVICE_ERROR_NORMAL,    // ��������� ������ ����������
    "C:\\DemoService.exe",   // ���� � �������
    NULL,                    // ������ �� ����������� � ������
    NULL,        // ��� ������ �� ����������
    NULL,        // ������ �� ������� �� ������ ��������
    NULL,        // ��� ��������� � ������� ������ ������� ������
    NULL         // ������ ���
  );
  if (hService == NULL)
  {
    cout << "Create service failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get(); 

    // ��������� ���������� ��������� ��������
    CloseServiceHandle(hServiceControlManager);

    return 0;
  }

  cout << "Service is installed." << endl
    << "Press any key to exit." << endl;
  cin.get();

  // ��������� �����������
  CloseServiceHandle(hService);
  CloseServiceHandle(hServiceControlManager);

  return 0;
}