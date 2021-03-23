#include <windows.h>
#include <iostream.h>

int main()
{
  int  *p = NULL;    // пустой указатель на целое число

  __try
  {
    if (!p)
    {
      cout << "Exit with goto from the try block." << endl;

      goto exit_try;   // выходим их блока
    }
    else
      *p = 10;
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    cout << "There was some exception." << endl;
  }

  cout << "*p = " << *p << endl;

exit_try: return 0;

}