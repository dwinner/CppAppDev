#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream.h>


int main()
{
  HANDLE  hTimer;    // ��������� ������

  // ��������� ������������ ��������� ������
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

  // ���� ������ �� ���������� �������
  WaitForSingleObject(hTimer, INFINITE);
  // ������� ���������
  cout << "\aThe timer is signaled." << endl;
  // ��������� ������
  CloseHandle(hTimer);
  // ���� ������� �� ����� �� ��������
  cout << "Press any key to exit." << endl;
  cin.get();

  return 0;
}