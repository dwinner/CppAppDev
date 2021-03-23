#include <windows.h>
#include <iostream.h>

int main()
{
  int  *p = NULL;    // пустой указатель на целое число

  __try
  {
    if (!p)
    {
      cout << "Exit with __leave from the try block." << endl;

      __leave;     // выходим их блока
    }
    else
    {
      *p = 10;

      cout << "*p = " << *p << endl;
    }
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    cout << "There was some exception." << endl;
  }

  return 0;

}