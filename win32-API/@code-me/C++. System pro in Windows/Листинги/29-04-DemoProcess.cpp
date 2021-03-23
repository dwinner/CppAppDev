#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>


int main()
{
  HANDLE  hTimer;    // ожидающий таймер

  // открываем существующий ожидающий таймер
  hTimer = OpenWaitableTimer(
    TIMER_ALL_ACCESS,
    FALSE,
    "demo_timer"
    );
  if (hTimer == NULL)
  {
    cout << "Open waitable timer failed." << endl
      << "The last error code: " << GetLastError() << endl;
    return 0;
  }

  // ждем сигнал от ожидающего таймера
  WaitForSingleObject(hTimer, INFINITE);
  // выводим сообщение
  cout << "\aThe timer is signaled." << endl;
  // закрываем таймер
  CloseHandle(hTimer);
  // ждем команды на выход из процесса
  cout << "Press any key to exit." << endl;
  cin.get();

  return 0;
}