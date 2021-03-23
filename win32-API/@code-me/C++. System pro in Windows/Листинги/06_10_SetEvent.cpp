#include <windows.h>
#include <iostream.h>

HANDLE hOutEvent, hAddEvent;

DWORD WINAPI thread(LPVOID)
{
  for (int i = 0; i < 10; ++i)
    if (i == 4)
    {
      SetEvent(hOutEvent);
      WaitForSingleObject(hAddEvent, INFINITE);
    }
    
  return 0;
}

int main()
{
  HANDLE  hThread;
  DWORD  IDThread;

  // ������� ������� � �������������� �������
  hOutEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (hOutEvent == NULL)
    return GetLastError();
  hAddEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (hAddEvent == NULL)
    return GetLastError();

  // ������� ����� thread
  hThread = CreateThread(NULL, 0, thread, NULL, 0, &IDThread);
  if (hThread == NULL)
    return GetLastError();

  // ����, ���� ����� thread �������� �������� ������
  WaitForSingleObject(hOutEvent, INFINITE);
  // ������� �������� ����������
  cout << "A half of the work is done." << endl;
  cout << "Press any key to continue." << endl;
  cin.get();
  // ��������� ������ �������� ������ thread
  SetEvent(hAddEvent);

  WaitForSingleObject(hThread, INFINITE);
  CloseHandle(hThread);

  CloseHandle(hOutEvent);
  CloseHandle(hAddEvent);

  cout << "The work is done." << endl;

  return 0;
}