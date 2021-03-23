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
    DWORD  ec = GetExceptionCode();    // �������� ��� ����������

    if (ec == EXCEPTION_ACCESS_VIOLATION)
      cout << "Exception access violation." << endl;
    else
      cout << "Some other exception." << endl;

    p = &a;
  }

  cout << "a = " << *p << endl;    // ���������

  return 0;
}