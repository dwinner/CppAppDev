#include <windows.h>
#include <iostream.h>

int main()
{
  int  a = 10; 
  int  *p = NULL;    // пустой указатель на целое число

  __try
  {
    cout << "a = " << *p << endl;  // ошибка, так как p = NULL
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    DWORD  ec = GetExceptionCode();    // получаем код исключения

    if (ec == EXCEPTION_ACCESS_VIOLATION)
      cout << "Exception access violation." << endl;
    else
      cout << "Some other exception." << endl;

    p = &a;
  }

  cout << "a = " << *p << endl;    // нормально

  return 0;
}