#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";  // имя сервиса
  SERVICE_STATUS  service_status;        // состояние сервиса
  SC_HANDLE  hServiceControlManager, hService;

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
    SERVICE_ALL_ACCESS | DELETE  // любой доступ к сервису 
                                 // и удаление из базы данных
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

  // получаем состояние сервиса
  if (!QueryServiceStatus(hService, &service_status))
  {
    cout << "Query service status failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // закрываем дескрипторы
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }

  // если сервис работает, то останавливаем его
  if (service_status.dwCurrentState != SERVICE_STOPPED)
  {
    cout << "Service is working. It will be stoped" << endl;
    if (!ControlService(hService, SERVICE_CONTROL_STOP, &service_status))
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

    // ждем, пока сервис остановится
    Sleep(500);
  }

  // удаляем сервис
  if (!DeleteService(hService))
  {
    cout << "Delete service failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // закрываем дескрипторы
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }

  cout << "The service is deleted." << endl
    << "Press any key to exit." << endl;
  cin.get();

  // закрываем дескрипторы
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hService);

  return 0;
}