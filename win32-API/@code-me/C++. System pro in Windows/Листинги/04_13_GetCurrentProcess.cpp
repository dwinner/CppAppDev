#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hProcess;

  // �������� ���������������� �������� ��������
  hProcess = GetCurrentProcess();
  // ������� ���������������� �� �������
  cout << hProcess << endl;

  cin.get();

  return 0;
}