#include <windows.h>
#include <iostream.h>

int main()
{
  __try
  {
    int *a, *b;

    __try
    {
      a = new int(10);

      __try
      {
        b = new int(0);
        // ошибка, деление на ноль
        cout << "a/b = " << (*a)/(*b) << endl;
      }
      __finally
      {
        // освобождаем память для 'b'
        delete b;
        cout << "The memory for 'b' is free." << endl;
      }
    }
    __finally
    {
      // освобождаем память для 'a'
      delete a;
      cout << "The memory for 'a' is free." << endl;
    }
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    cout << "There was some exception." << endl;
  }

  return 0;
}