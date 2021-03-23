#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";    // имя сервиса
  SC_HANDLE  hServiceControlManager, hService;
  SERVICE_STATUS  service_status;

  // связываемся с менеджером сервисов
  hServiceControlManager = OpenSCManager(
    NULL,      // локальная машина
    NULL,      // активная база данных сервисов
    SC_MANAGER_CONNECT   // соединение с менеджером сервисов
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

  // открываем сервис
  hService = OpenService(
    hServiceControlManager,  // дескриптор менеджера сервисов
    service_name,            // имя сервиса
    SERVICE_ALL_ACCESS       // любой доступ к сервису
  );
  if (hService == NULL)
  {
    cout << "Open service failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // закрываем дескриптор менеджера сервисов
    CloseServiceHandle(hServiceControlManager);

    return 0;
  }

  cout << "Service is opened." << endl
    << "Press any key to continue." << endl;
  cin.get();

  // определение состояния сервиса
  if (!QueryServiceStatus(
    hService,        // дескриптор сервиса
    &service_status  // адрес структуры состояния сервиса
    ))
  {
    cout << "Query service sataus failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // закрываем дескрипторы
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

  // закрываем дескрипторы
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hService);

  return 0;
}