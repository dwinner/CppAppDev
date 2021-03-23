#include <windows.h>
#include <iostream.h>

int main()
{
  SC_HANDLE  hServiceControlManager, hService;

  // связываемся с менеджером сервисов
  hServiceControlManager = OpenSCManager(
    NULL,      // локальная машина
    NULL,      // активная база данных сервисов
    SC_MANAGER_CREATE_SERVICE  // возможно создание сервиса
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

  // устанавливаем новый сервис
  hService = CreateService(
    hServiceControlManager,  // дескриптор менеджера сервисов
    "DemoService",           // внутреннее имя сервиса, используемое SCM
    "Demo_Service",          // внешнее имя сервиса в панели управления
    SERVICE_ALL_ACCESS,      // полный контроль над сервисом
    SERVICE_WIN32_OWN_PROCESS,   // сервис является процессом
    SERVICE_DEMAND_START,    // запускается сервис по требованию
    SERVICE_ERROR_NORMAL,    // обработка ошибок нормальная
    "C:\\DemoService.exe",   // путь к сервису
    NULL,                    // сервис не принадлежит к группе
    NULL,        // тэг группы не изменяется
    NULL,        // сервис не зависит от других сервисов
    NULL,        // имя совпадает с текущим именем учетной записи
    NULL         // пароля нет
  );
  if (hService == NULL)
  {
    cout << "Create service failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get(); 

    // закрываем дескриптор менеджера сервисов
    CloseServiceHandle(hServiceControlManager);

    return 0;
  }

  cout << "Service is installed." << endl
    << "Press any key to exit." << endl;
  cin.get();

  // закрываем дескрипторы
  CloseServiceHandle(hService);
  CloseServiceHandle(hServiceControlManager);

  return 0;
}