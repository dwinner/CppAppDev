#include <windows.h>
#include <iostream.h>

int main()
{

  char big[] = "�����Ũ��������������������������";
  char sml[] = "��������������������������������";

  CharToOem(big,big);
  CharToOem(sml,sml);

  cout << big << endl;
  cout << sml << endl;

  return 0;
}