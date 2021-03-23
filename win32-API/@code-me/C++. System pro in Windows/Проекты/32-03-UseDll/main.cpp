#include <windows.h>
#include <iostream.h>

int (*Add)(int);   // ��������� �� ������� Add �� DLL

DWORD WINAPI thread(LPVOID iNum)
{
  for (int i = 0; i < (int)iNum; ++i)
  {
    cout << "count = " << Add((int)iNum) << endl;
    Sleep(15);
  }

  return 0;
}

int main()
{
  char  c;
  HMODULE  hDll;       // ���������� DLL
  HANDLE  hThread[2];  // ����������� �������
  DWORD  IDThread[2];  // �������������� �������

  // ��������� ����������� ������������ ����������
  hDll = LoadLibrary("Count.dll");
  if (!hDll)
  {
    cerr << "Load library failed." << endl;
    return GetLastError();
  }
  // ����������� ����� ������
  Add = (int (*)(int))GetProcAddress(hDll, "Add");
  if (!Add)
  {
    cerr << "Get procedure address failed." << endl;
    return GetLastError();
  }
  // ��������� ������
  hThread[0] = CreateThread(NULL, 0, thread, (void*)3, 0, &IDThread[0]);
  hThread[1] = CreateThread(NULL, 0, thread, (void*)5, 0, &IDThread[1]);
  if (hThread[0] == NULL || hThread[1] == NULL)
  {
    cerr << "Create thread failed." << endl;
    return GetLastError();
  }
  // ���� ���������� �������
  WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
  // ��������� ����������
  if (!FreeLibrary(hDll))
  {
    cerr << "Free library failed." << endl;
    return GetLastError();
  }
  // ������� �� ���������
  cout << "Input any char to exit: ";
  cin >> c;

  return 0;
}