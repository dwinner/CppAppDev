#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";    // имя сервиса
  SC_HANDLE  hServiceControlManager, hService;
  
  // указатель на буфер для информации о конфигурации сервиса
  QUERY_SERVICE_CONFIG*  lpQueryServiceConfig;
  // переменная для размера структуры в случае неудачи функции
  DWORD  dwBytesNeeded;

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

  // захватываем память под буфер
  lpQueryServiceConfig = (LPQUERY_SERVICE_CONFIG)new char[4096];

  // определяем конфигурацию сервиса
  if (!QueryServiceConfig(
    hService,              // дескриптор сервиса
    lpQueryServiceConfig,  // адрес структуры конфигурации сервиса
    4096,                  // размер этой структуры
    &dwBytesNeeded         // необходимое количество байтов
    ))
  {
    cout << "Query service configuartion failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // закрываем дескрипторы
    CloseServiceHandle(hServiceControlManager);
    CloseServiceHandle(hService);

    return 0;
  }
  // распечатываем информацию о конфигурации
  cout << "Service type: " << lpQueryServiceConfig->dwServiceType << endl
    << "Start type: " << lpQueryServiceConfig->dwStartType << endl
    << "Error control: " << lpQueryServiceConfig->dwErrorControl << endl
    << "Binary path name: " << lpQueryServiceConfig->lpBinaryPathName 
    << endl
    << "Service start name: " << lpQueryServiceConfig->lpServiceStartName 
    << endl
    << "Display name: " << lpQueryServiceConfig->lpDisplayName << endl
    << endl;
  // освобождаем память
  delete[] lpQueryServiceConfig;

  cout << "Press any key to exit." << endl;
  cin.get();

  // закрываем дескрипторы
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hService);

  return 0;
}