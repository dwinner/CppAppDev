#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hThread;

  // �������� ���������������� �������� ������
  hThread = GetCurrentThread();
  // ������� ���������������� �� �������
  cout << hThread << endl;

  cin.get();

  return 0;
}