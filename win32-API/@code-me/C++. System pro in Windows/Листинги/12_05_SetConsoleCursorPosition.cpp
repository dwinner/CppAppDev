#include <windows.h>
#include <iostream.h>

int main()
{
  char  c;
  HANDLE  hStdOut;   // ���������� ������������ ������
  COORD  coord;      // ��� ������� �������

  // ������ ���������� ������������ ������
  hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  cout << "Input new cursor position." << endl;
  cout << "X = ";
  cin >> coord.X;
  cout << "Y = ";
  cin >> coord.Y;

  // ���������� ������ � ����� �������
  if (!SetConsoleCursorPosition(hStdOut, coord))
  {
    cout << "Set cursor position failed." << endl;
    return GetLastError();
  }

  cout << "This is a new position." << endl;
  cout << "Input any char to exit: ";
  cin >> c;

  return 0;  
}