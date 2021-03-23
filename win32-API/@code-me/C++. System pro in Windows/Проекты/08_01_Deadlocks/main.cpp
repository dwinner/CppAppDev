#include <windows.h>
#include <iostream.h>
#include <math.h>

const int size = 10;   // ����������� �������
int    a[size];        // �������������� ������
HANDLE  hDeadlock;     // ������ � ������
HANDLE  hAnswer[2];    // ��� ��������� ������

DWORD WINAPI marker(LPVOID)
{
  int    i;
  DWORD  dwValue; 

  for (;;)
  {
    // ��������� ��������� ������
    i = abs(rand()) % size;
    // ���������, ����� �� �������
    if (!a[i])
      // ���, ��������� �������
      a[i] = 1;  
    else
    {
      // ��, ������������� � ������
      SetEvent(hDeadlock);
      // ���� ������
      dwValue = WaitForMultipleObjects(
              2, hAnswer, FALSE, INFINITE);
      if (dwValue == WAIT_FAILED)
      {
        cerr << "Wait function failed." << endl;
        cerr << "Press any key to exit." << endl;
        cin.get();

        return GetLastError();
      }
      // ��������� ������ ����������� �������
      dwValue -= WAIT_OBJECT_0;
      switch (dwValue)
      {
      case 0:    // ���������� ������
        continue;
      case 1:    // ��������� ������
        ExitThread(1);
        break;
      default:
        ExitThread(2);
        break;
      }
    }
  }
}

int main()
{
  HANDLE  hMarker;
  DWORD  idMarker;

  // ������� �������, ����������� � ������
  hDeadlock = CreateEvent(NULL, FALSE, FALSE, NULL);
  // ������� ������� ��� ��������� ������
  hAnswer[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
  hAnswer[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
  // ��������� ����� marker
  hMarker = CreateThread(NULL, 0, marker,NULL, 0, &idMarker);
  if (hMarker == NULL)
    return GetLastError();
  for (;;)
  {
    char c;
    // ���� ������ � ������
    WaitForSingleObject(hDeadlock, INFINITE);
    // ������� �� ������� ������� ��������� �������
    cout << "Current state of the array: ";
    for (int i = 0; i < size; ++i)
      cout << a[i] << ' ';
    cout << endl;
    // ��������� ��� ��� ����� marker?
    cout << "Input 'y' to continue: ";
    cin >> c;
    if (c == 'y')
      SetEvent(hAnswer[0]);  // ���������� ������
    else
    {
      SetEvent(hAnswer[1]);  // ��������� ������
      break;
    }
  }

  WaitForSingleObject(hMarker, INFINITE);
  CloseHandle(hMarker);

  return 0;
}