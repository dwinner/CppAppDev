#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

#define _SECOND 10000000   // одна секунда для ожидающего таймера

VOID CALLBACK completion_proc(LPVOID lpArg, 
         DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
  // выводим сообщение
  cout << "\aThe timer is signaled." << endl;
  // распечатываем аргументы
  cout << "Arguments: " << (char*)lpArg << endl
    << "Timer low value: " << dwTimerLowValue << endl
    << "Timer high value: " << dwTimerHighValue << endl;
}

int main()
{
  HANDLE  hTimer;            // ожидающий таймер

  _int64  qwTimeInterval;    // время задержки для таймера

  // создаем ожидающий таймер
  hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
  if (hTimer == NULL)
    return GetLastError();

  // время задержки для таймера = 1 секунда
  qwTimeInterval = -1 * _SECOND;

  // инициализируем таймер
  if (!SetWaitableTimer(
    hTimer,              // дескриптор таймера
    (LARGE_INTEGER*)&qwTimeInterval,   // временной интервал
    0,                   // не периодический таймер
    completion_proc,     // процедура завершения
    "Demo parameters.",  // параметров к этой процедуре нет
    FALSE                // режим сбережения энергии не устанавливать
    ))
  {
    cout << "Set waitable timer failed." << endl
      << "The last error code: " << GetLastError() << endl;

    return 0;
  }
  // переводим поток в настороженное состояние
  SleepEx(INFINITE, TRUE);

  // закрываем таймер
  CloseHandle(hTimer);

  return 0;
}