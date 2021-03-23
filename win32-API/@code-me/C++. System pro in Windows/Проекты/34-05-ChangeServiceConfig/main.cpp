#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";    // им€ сервиса
  SC_HANDLE  hServiceControlManager, hService;
  
  // указатель на буфер дл€ информации о конфигурации сервиса
  QUERY_SERVICE_CONFIG*  lpQueryServiceConfig;
  // переменна€ дл€ размера структуры в случае неудачи функции
  DWORD  dwBytesNeeded;

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

  // захватываем пам€ть под буфер
  lpQueryServiceConfig = (LPQUERY_SERVICE_CONFIG)new char[4096];

  // определ€м конфигурацию сервиса
  QueryServiceConfig( hService, lpQueryServiceConfig, 4096, 
                      &dwBytesNeeded);
  // распечатываем информацию о режиме запуска сервиса
  cout << "Old start type: " << lpQueryServiceConfig->dwStartType 
       << endl;

  // измен€ем режим запуска сервиса
  if (!ChangeServiceConfig(
    hService,              // дескриптор сервиса
    SERVICE_NO_CHANGE,     // тип сервиса не измен€ем
    SERVICE_AUTO_START,    // запуск во врем€ загрузки системы
    SERVICE_NO_CHANGE,     // режим обработки ошибок не измен€ем
    NULL, NULL, NULL, NULL, NULL, NULL, NULL  // все остальные параметры 
                                              // конфигурации не измен€ем
    ))
  {
    cout << "Change service configuration failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // закрываем дескрипторы
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }

  // определ€м конфигурацию сервиса
  QueryServiceConfig( hService, lpQueryServiceConfig, 4096, 
                     &dwBytesNeeded);
  // распечатываем информацию о режиме запуска сервиса
  cout << "New start type: " << lpQueryServiceConfig->dwStartType 
       << endl;

  // восстанавливаем режим запуска сервиса
  ChangeServiceConfig(
    hService,              // дескриптор сервиса
    SERVICE_NO_CHANGE,     // тип сервиса не измен€ем
    SERVICE_DEMAND_START,  // запуск во врем€ загрузки системыпо требованию
    SERVICE_NO_CHANGE,     // режим обработки ошибок не измен€ем
    NULL, NULL, NULL, NULL, NULL, NULL, NULL  // все остальные параметры 
                                              // конфигурации не измен€ем
    );
  // определ€м конфигурацию сервиса
  QueryServiceConfig( hService, lpQueryServiceConfig, 4096, 
                     &dwBytesNeeded);
  // распечатываем информацию о режиме запуска сервиса
  cout << "Old start type: " << lpQueryServiceConfig->dwStartType 
       << endl;

  // освобождаем пам€ть
  delete[] lpQueryServiceConfig;

  cout << "Press any key to exit." << endl;
  cin.get();

  // закрываем дескрипторы
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hService);

  return 0;
}