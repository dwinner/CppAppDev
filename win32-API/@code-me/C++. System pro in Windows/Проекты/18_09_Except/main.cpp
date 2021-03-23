#include <windows.h>
#include <iostream.h>

void f(int *p)
{
  int  a = 10;

  *p = a;    // ошибка, так как пустой указатель
}

void g(int *p)
{
  int a = 0;

  *p /= a;     // ошибка, деление на ноль
}

int main()
{
  int a = 10;
  int  *p = NULL;    // пустой указатель на целое число

  __try
  {
    __try
    {
      f(p);
    }
    __except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
      EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
    {
      cout << "Exception access violation." << endl;
    }

    p = &a;    // указатель не пустой

    __try
    {
      g(p);
    }
    __except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
      EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
    {
      cout << "Exception access violation." << endl;
    }
  }
  __except(GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ?
    EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
  {
    cout << "Exception integer divide by zero." << endl;
  }

  return 0;
}