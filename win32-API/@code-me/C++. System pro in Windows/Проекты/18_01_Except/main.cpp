#include <windows.h>
#include <iostream.h>

int main()
{
  int  a = 10; 
  int  *p = NULL;    // ������ ��������� �� ����� �����

  __try
  {
    cout << "a = " << *p << endl;  // ������, ��� ��� p = NULL
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    cout << "There was some exception." << endl;
    p = &a;
  }

  cout << "a = " << *p << endl;    // ���������

  return 0;
}