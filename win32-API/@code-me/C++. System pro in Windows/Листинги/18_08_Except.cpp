#include <windows.h>
#include <iostream.h>
#include <float.h>

int main()
{
  double  a = 0;

  // получить управляющее слово, заданное по умолчанию
  int cw = _controlfp( 0, 0 );
  // разрешить обработку исключений с плавающей точкой
  cw &=~(EM_OVERFLOW | EM_UNDERFLOW 
        | EM_INEXACT | EM_ZERODIVIDE | EM_DENORMAL);
  // установить новое управляющее слово
  _controlfp( cw, _MCW_EM );
  // теперь можно обрабатывать исключения
  __try
  {
    double  b;

    b = 1/a;  // ошибка, деление на 0
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    DWORD  ec = GetExceptionCode();  // получаем код исключения

    if (ec == EXCEPTION_FLT_DIVIDE_BY_ZERO)
      cout << "Exception float divide by zero." << endl;
    else
      cout << "Some other exception." << endl;

  }

  return 0;
}