#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

#define _SECOND 10000000   // одна секунда для ожидающего таймера

HANDLE  hHandle[2];  // событие для выхода из цикла и ожидающий таймер

DWORD WINAPI thread(LPVOID)
{
  DWORD  dwRetCode;  // код возврата из функции ожидания

  for (;;)
  {
    // ждем сигнал от ожидающего таймера или на выход из цикла
    dwRetCode = WaitForMultipleObjects(2, hHandle, FALSE, INFINITE);
    // определяем индекс дескриптора
    dwRetCode -= WAIT_OBJECT_0;

    switch (dwRetCode)
    {
    case 0:    // сработало событие
      cout << "The timer is canceled." << endl;
      return 0;
    case 1:    // сработал таймер
      cout << "\aThe waitable timer is signaled." << endl;
      break;
    default:
      cout << "Default statement." << endl;
      return 0;
    }
  }
}

int main()
{
  HANDLE  hThread;
  DWORD  IDThread;

  _int64  qwTimeInterval;    // время задержки для таймера

  // создаем события с автоматическим сбросом
  hHandle[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (hHandle[0] == NULL)
    return GetLastError();

  // создаем ожидающий таймер
  hHandle[1] = CreateWaitableTimer(
      NULL,    // защиты нет
      FALSE,   // автоматический сброс
      NULL     // имени нет
    );
  if (hHandle[1] == NULL)
    return GetLastError();

  // время задержки для таймера = 2 секунды
  qwTimeInterval = -2 * _SECOND;

  // инициализируем таймер
  if (!SetWaitableTimer(
    hHandle[1],  // дескриптор таймера
    (LARGE_INTEGER*)&qwTimeInterval,  // временной интервал
    2000,    // период = 2 секунды
    NULL,    // процедуры завершения нет
    NULL,    // параметров к этой процедуре нет
    FALSE    // режим сбережения энергии не устанавливать
    ))
  {
    cout << "Set waitable timer failed." << endl
      << "The last error code: " << GetLastError() << endl;

    return 0;
  }

  // запускаем поток
  hThread = CreateThread(NULL, 0, thread, NULL, 0, &IDThread);
  if (hThread == NULL)
    return GetLastError();

  // ждем команды на снятие ожидающего таймера
  char  c;
  cout << "Input any char to cancel waitable timer." << endl;
  cin >> c;

  // снимаем ожидающий таймер
  CancelWaitableTimer(hHandle[1]);

  // даем потоку сигнал на завершение работы
  SetEvent(hHandle[0]);

  // ждем, пока поток закончит работу
  WaitForSingleObject(hThread, INFINITE);
  // закрываем дескрипторы
  CloseHandle(hHandle[0]);
  CloseHandle(hHandle[1]);

  return 0;
}