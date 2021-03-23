#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";    // им€ сервиса
  SC_HANDLE  hServiceControlManager, hService;
  SERVICE_STATUS  service_status;

  // св€зываемс€ с менеджером сервисов
  hServiceControlManager = OpenSCManager(
    NULL,      // локальна€ машина
    NULL,      // активна€ база данных сервисов
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
    service_name,            // им€ сервиса
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

  // останавливаем сервис
  if (!ControlService(
    hService,              // дескриптор сервиса
    SERVICE_CONTROL_STOP,  // управл€юща€ команда
    &service_status        // адрес структуры состо€ни€ сервиса
    ))
  {
    cout << "Control service failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // закрываем дескрипторы
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }

  cout << "The service is stopped." << endl
    << "Press any key to exit." << endl;
  cin.get();

  // закрываем дескрипторы
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hService);

  return 0;
}