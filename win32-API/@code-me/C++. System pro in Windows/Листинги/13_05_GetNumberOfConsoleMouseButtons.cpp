#include <windows.h>
#include <iostream.h>

int main() 
{
  DWORD  dwNumber;     // ��� ���������� ������ � ����

  // ������������ ���������� ������ � ����
  if (!GetNumberOfConsoleMouseButtons(&dwNumber))
  {
    cout << "Get number of console mouse buttons failed." << endl;
    return GetLastError();
  }
  // ������� ���������� ������ � ����
  cout << "Number of console mouse buttons = " << dwNumber << endl;

  return 0; 
}