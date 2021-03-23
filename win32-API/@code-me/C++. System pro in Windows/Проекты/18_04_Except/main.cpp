#include <windows.h>
#include <iostream.h>


DWORD filter_function(DWORD  ec, int &a)
{
    // ��������� ��� ����������
  if (ec == EXCEPTION_INT_DIVIDE_BY_ZERO)
  {
    cout << "Integer divide by zero exception." << endl;
    cout << "a = " << a << endl;

      // ��������������� ������
    a = 10;

      // ������������ ���������� ���������
    cout << "Continue execution." << endl;
    cout << "a = " << a << endl;

    return EXCEPTION_CONTINUE_EXECUTION;
  }

  else
      // ���������� ���������� ���������
    return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
  int a = 0;
  int b = 1000;

  __try
  {
    b /= a;
    cout << "b = " << b << endl;
  }
  __except(filter_function(GetExceptionCode(), a))
  {
    cout << "There was some exception." << endl;
  }

  return 0;
}