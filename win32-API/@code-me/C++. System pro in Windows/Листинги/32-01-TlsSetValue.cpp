#include <windows.h>
#include <iostream.h>

DWORD thread(void)
{
  char  c;
  DWORD  dwFirstTlsIndex, dwPrevTlsIndex, dwNextTlsIndex;

  // ������������ ������ tls ������
  dwFirstTlsIndex = TlsAlloc();
  if (dwFirstTlsIndex == -1)
  {
    cerr << "Tls allocation failed." << endl;
    return GetLastError();
  }
  // ������������� ���������� tls ������ ������ ������� �������
  dwPrevTlsIndex = dwFirstTlsIndex;
  // ��������� ������ �� tls ��������
  for (;;)
  {
    // ������� �� ����� ���������� tls ������
    cout << "Alloc tls index = " << dwPrevTlsIndex << endl;
    Sleep(50);
    // ������������ ��������� tls ������
    dwNextTlsIndex = TlsAlloc();
    // ���� ������ �������� ���, �� ������� �� �����
    if (dwNextTlsIndex == -1)
      break;
    // �������� ��������� tls ������ � ���������� �������
    if (!TlsSetValue(dwPrevTlsIndex, (LPVOID)dwNextTlsIndex))
    {
      cerr << "Tls set value failed." << endl;
      return GetLastError();
    }
    // ���������� �������
    dwPrevTlsIndex = dwNextTlsIndex;
  }

  // ���� ������� �� ������������ ��������
  cout << "Input any char to free tls indexes: ";
  cin >> c;

  // ������������� ���������� tls ������ � ������
  dwPrevTlsIndex = dwFirstTlsIndex;
    // ��������� ������ �� tls ��������
  for (;;)
  {
    // ������� �� ����� ���������� tls ������ 
    cout << "Free tls index = " << dwPrevTlsIndex << endl;
    Sleep(50);
    // �������� ��������� tls ������
    dwNextTlsIndex = (DWORD)TlsGetValue(dwPrevTlsIndex);
    if (!dwNextTlsIndex)
      break;
    // ����������� ���������� tls ������
    if (!TlsFree(dwPrevTlsIndex))
    {
      cerr << "Tls free failed." << endl;
      return GetLastError();
    }
    // ���������� �������
    dwPrevTlsIndex = dwNextTlsIndex;
  }

  // ���� ������� �� ����� �� ������
  cout << "Input any char to exit: ";
  cin >> c;

  return 0;
}

int main()
{
  HANDLE  hThread;
  DWORD  IDThread;

  // ��������� �����
  hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, 
               NULL, 0, &IDThread);
  if (hThread == NULL)
  {
    cerr << "Create thread failed." << endl;
    return GetLastError();
  }
  // ����, ���� ����� Add �������� ������
  WaitForSingleObject(hThread, INFINITE);
  // ��������� ���������� ������
  CloseHandle(hThread);

  return 0;
}