#include <windows.h>
#include <iostream.h>

int main()
{
  char  ConsoleTitleBuffer[1024];  // ��������� �� ����� � ����������
  DWORD  dwBufferSize = 1024;      // ������ ������ ��� ���������
  DWORD  dwTitleSize;            // ����� ���������

  // ������ ��������� �������
  dwTitleSize = GetConsoleTitle(ConsoleTitleBuffer, dwBufferSize);

  // ������� �� ������� ���������
  cout << "Title length = " << dwTitleSize << endl;
  cout << "The window title = " << ConsoleTitleBuffer << endl;

  cout << "Input new title: ";
  cin.getline(ConsoleTitleBuffer, 80);
  // ������������� ����� ��������� �������
  if (!SetConsoleTitle(ConsoleTitleBuffer))
    cout << "Set console title failed." << endl;

  cout << "The title was changed." << endl;
  cout << "Press any key to exit.";
  cin.get();

  return 0;
}