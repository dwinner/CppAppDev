#include <windows.h>
#include <iostream.h>

int main()
{
  char c;
  int  *p = NULL;  // ������ ��������� �� ����� �����

  // ������� 'y', ����� ������������ ������ ��� ����� �����
  cout << "Input 'y' to allocate memory: ";
  // ������ ������
  cin >> c;
  // ���� ����� 'y', �� ������ ��������������, ����� - �� ��������������
  if (c == 'y')
    p = new int;

  __try
  {
    *p = 10;  // ����� ���� ����������, ���� ������ �� ������������
  }
  __finally
  {
    // � ����� ������ ������� ���������� ������
    delete p;
    // ������� ���������
    cout << "The finally block finished." << endl;
  }

  return 0;
}