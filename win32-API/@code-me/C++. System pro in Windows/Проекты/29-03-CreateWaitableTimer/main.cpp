#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>

#define _SECOND 10000000   // одна секунда для ожидающего таймера

int main()
{
  HANDLE  hTimer;          // ожидающий таймер

  _int64  qwTimeInterval;  // время задержки для таймера

  // создаем ожидающий таймер
  hTimer = CreateWaitableTimer(NULL, FALSE, "demo_timer");
  if (hTimer == NULL)
    return GetLastError();

  // время задержки для таймера = 2 секунды
  qwTimeInterval = -2 * _SECOND;

  // инициализируем таймер
  if (!SetWaitableTimer(
    hTimer,  // дескриптор таймера
    (LARGE_INTEGER*)&qwTimeInterval,  // временной интервал
    0,       // не периодический таймер
    NULL,    // процедуры завершения нет
    NULL,    // параметров к этой процедуре нет
    FALSE    // режим сбережения энергии не устанавливать
    ))
  {
    cout << "Set waitable timer failed." << endl
      << "The last error code: " << GetLastError() << endl;

    return 0;
  }

  // создаем новый консольный процесс
  char lpszAppName[] = "C:\\DemoProcess.exe";

  STARTUPINFO si;
  PROCESS_INFORMATION piApp;

  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);

  if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
      CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
  {
    cout << "The new process is not created." << endl
      << "Check a name of the process." << endl
      << "Press any key to finish." << endl;

    cin.get();

    return 0;
  }

  // ждем завершения созданного процесса
  WaitForSingleObject(piApp.hProcess, INFINITE);
  // закрываем дескрипторы этого процесса в текущем процессе
  CloseHandle(piApp.hThread);
  CloseHandle(piApp.hProcess);

  // закрываем таймер
  CloseHandle(hTimer);

  return 0;
}