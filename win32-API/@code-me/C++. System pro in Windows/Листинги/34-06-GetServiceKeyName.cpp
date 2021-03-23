#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";  // имя сервиса
  SC_HANDLE  hServiceControlManager;   // дескриптор базы данных сервисов

  // указатель на буфер для внутреннего имени сервиса
  char*  lpszServiceName;
  // переменная для длины буфера в случае неудачи функции
  DWORD  dwBufferSize;

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

  // захватываем память под буфер
  dwBufferSize = 256;
  lpszServiceName = (char*)new char[dwBufferSize];

  // определение внутреннего имени сервиса
  if (!GetServiceKeyName(
    hServiceControlManager,    // дескриптор базы данных сервисов
    "Demo_Service",    // внешнее имя сервиса
    lpszServiceName,   // буфер для имени сервиса
    &dwBufferSize      // количество необходимых байтов
    ))
  {
    cout << "Get service key name failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // закрываем дескриптор базы данных сервисов
    CloseServiceHandle(hServiceControlManager);

    return 0;
  }

  // выводим на консоль внутреннее имя сервиса
  cout << "Service key name: " << lpszServiceName << endl;

  cout << "Press any key to exit." << endl;
  cin.get();

  // закрываем дескриптор базы данных сервисов
  CloseServiceHandle(hServiceControlManager);

  return 0;
}