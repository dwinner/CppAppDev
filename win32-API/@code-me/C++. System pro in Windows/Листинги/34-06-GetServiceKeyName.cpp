#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";  // ��� �������
  SC_HANDLE  hServiceControlManager;   // ���������� ���� ������ ��������

  // ��������� �� ����� ��� ����������� ����� �������
  char*  lpszServiceName;
  // ���������� ��� ����� ������ � ������ ������� �������
  DWORD  dwBufferSize;

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

  // ����������� ������ ��� �����
  dwBufferSize = 256;
  lpszServiceName = (char*)new char[dwBufferSize];

  // ����������� ����������� ����� �������
  if (!GetServiceKeyName(
    hServiceControlManager,    // ���������� ���� ������ ��������
    "Demo_Service",    // ������� ��� �������
    lpszServiceName,   // ����� ��� ����� �������
    &dwBufferSize      // ���������� ����������� ������
    ))
  {
    cout << "Get service key name failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // ��������� ���������� ���� ������ ��������
    CloseServiceHandle(hServiceControlManager);

    return 0;
  }

  // ������� �� ������� ���������� ��� �������
  cout << "Service key name: " << lpszServiceName << endl;

  cout << "Press any key to exit." << endl;
  cin.get();

  // ��������� ���������� ���� ������ ��������
  CloseServiceHandle(hServiceControlManager);

  return 0;
}