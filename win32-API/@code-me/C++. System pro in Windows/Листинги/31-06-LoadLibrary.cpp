#include <windows.h>
#include <iostream.h>

int main()
{
  HMODULE  hDll;     // ���������� DLL
  int (*Add)(int);   // ��������� �� ������� Add �� DLL
  int (*Sub)(int);   // ��������� �� ������� Sub �� DLL
  int *pCount;       // ��������� �� ���������� count �� DLL

  // ��������� ����������� ������������ ����������
  hDll = LoadLibrary("Count.dll");
  if (!hDll)
  {
    cerr << "Load library failed." << endl;
    return GetLastError();
  }
  // ����������� ����� ���������� count �� DLL
  pCount = (int *)GetProcAddress(hDll, MAKEINTRESOURCE(1));
  if (!pCount)
  {
    cerr << "Get variable address failed." << endl;
    return GetLastError();
  }
  // ������� ��������� �������� ���������� count
  cout << "Initial count = " << (*pCount) << endl;
  // ����������� ������ �������
  Add = (int (*)(int))GetProcAddress(hDll, MAKEINTRESOURCE(2));
  Sub = (int (*)(int))GetProcAddress(hDll, MAKEINTRESOURCE(3));
  if (!Add || !Sub)
  {
    cerr << "Get procedure address failed." << endl;
    return GetLastError();
  }
  // �������� �������� ��������
  cout << "count = " << Add(20) << endl;
  cout << "count = " << Sub(15) << endl;
  // ��������� ����������
  if (!FreeLibrary(hDll))
  {
    cerr << "Free library failed." << endl;
    return GetLastError();
  }
  // ������� �� ���������
  cout << "Press any key to exit.";
  cin.get();

  return 0;
}