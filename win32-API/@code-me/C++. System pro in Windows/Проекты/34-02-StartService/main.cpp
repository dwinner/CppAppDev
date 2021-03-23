#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";    // имя сервиса
  char  *param[] = { "p1", "p2", "p3" };   // список параметров
  SC_HANDLE  hServiceControlManager, hService;

  // связываемся с менеджером сервисов
  hServiceControlManager = OpenSCManager(
    NULL,    // локальная машина
    NULL,    // активная база данных сервисов
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
    SERVICE_ALL_ACCESS       // полный доступ к сервису
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

  // стартуем сервис
  if (!StartService(
    hService,    // дескриптор сервиса
    3,           // три параметра
    (const char**)param  // указатель на массив параметров
    ))
  {
    cout << "Start service failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // закрываем дескрипторы
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }

  cout << "The service is started." << endl
    << "Press any key to exit." << endl;
  cin.get();

  // закрываем дескрипторы
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hService);

  return 0;
}