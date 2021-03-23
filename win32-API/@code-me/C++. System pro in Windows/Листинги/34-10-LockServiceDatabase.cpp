#include <windows.h>
#include <iostream.h>

int main()
{
  char  service_name[] = "DemoService";  // имя сервиса
  SC_HANDLE  hServiceControlManager;  // дескриптор базы данных сервисов
  SC_LOCK    hScLock;  // дескриптор блокировки базы данных сервисов

  // указатель на буфер для состояния о блокировке
  LPQUERY_SERVICE_LOCK_STATUS    lpLockStatus;
  // длина буфера
  DWORD  dwBufferSize;
  // переменная для длины буфера в случае неудачи функции
  DWORD  dwBytesNeeded;

  // связываемся с менеджером сервисов
  hServiceControlManager = OpenSCManager(
    NULL,      // локальная машина
    NULL,      // активная база данных сервисов
    SC_MANAGER_LOCK |              // разрешено блокировка базы данных 
    SC_MANAGER_QUERY_LOCK_STATUS   // и определения состояния блокировки
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

  // блокируем базу данных сервисов
  hScLock = LockServiceDatabase(hServiceControlManager);
  if (hScLock == NULL)
  {
    cout << "Lock service database failed." << endl
      << "The last error code: " << GetLastError() << endl
      << "Press any key to exit." << endl;
    cin.get();

    // закрываем дескриптор базы данных сервисов
    CloseServiceHandle(hServiceControlManager);

    return 0;
  }

  cout << "\tThe service database is locked." << endl;

  // захватываем память под буфер
  dwBufferSize = 4096;
  lpLockStatus = (LPQUERY_SERVICE_LOCK_STATUS)new char[dwBufferSize];
  // определяем состояние блокировки
  QueryServiceLockStatus(hServiceControlManager, lpLockStatus, 
                         dwBufferSize, &dwBytesNeeded);
  // выводим на консоль состояние блокировки
  cout << "Lock state: " << lpLockStatus->fIsLocked << endl
    << "Lock owner: " << lpLockStatus->lpLockOwner << endl
    << "Lock duration: " << lpLockStatus->dwLockDuration << endl;

  // разблокируем базу данных сервисов
  UnlockServiceDatabase(hScLock);

  cout << "\tThe service database is unlocked." << endl;

  // определяем состояние блокировки
  QueryServiceLockStatus(hServiceControlManager, lpLockStatus, 
                         dwBufferSize, &dwBytesNeeded);
  // выводим на консоль состояние блокировки
  cout << "Lock state: " << lpLockStatus->fIsLocked << endl
    << "Lock owner: " << lpLockStatus->lpLockOwner << endl
    << "Lock duration: " << lpLockStatus->dwLockDuration << endl;

  cout << "Press any key to exit." << endl;
  cin.get();

  // закрываем дескрипторы
  CloseServiceHandle(hServiceControlManager);
  CloseServiceHandle(hScLock);

  return 0;
}