#include <windows.h>
#include <iostream.h>

int main()
{
  int  a = 10; 
  int  *p = NULL;

  __try
  {
    cout << "a = " << *p << endl;  // ошибка, так как p = NULL
  }
  __except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
    EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
  {
    cout << "Exception access violation." << endl;
    p = &a;
  }

  cout << "a = " << *p << endl;    // нормально  

  return 0;
}