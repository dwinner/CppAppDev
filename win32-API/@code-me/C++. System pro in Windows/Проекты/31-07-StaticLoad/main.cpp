#include <windows.h>
#include <iostream.h>

extern "C" __declspec(dllimport) int count;
extern "C" __declspec(dllimport) int Add(int n);
extern "C" __declspec(dllimport) int Sub(int n);

int main()
{
  // ������� ��������� �������� ���������� count
  cout << "Initial count = " << count << endl;
  // �������� �������� ��������
  cout << "count = " << Add(20) << endl;
  cout << "count = " << Sub(15) << endl;

  // ������� �� ���������
  cout << "Press any key to exit.";
  cin.get();

  return 0;
}